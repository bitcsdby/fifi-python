#! /usr/bin/env python
# encoding: utf-8

import os
from waflib.TaskGen import feature, after_method

APPNAME = 'fifi-python'
VERSION = '1.0.1'


def recurse_helper(ctx, name):
    if not ctx.has_dependency_path(name):
        ctx.fatal('Load a tool to find %s as system dependency' % name)
    else:
        p = ctx.dependency_path(name)
        ctx.recurse([p])


def options(opt):

    import waflib.extras.wurf_dependency_bundle as bundle
    import waflib.extras.wurf_dependency_resolve as resolve

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='boost',
        git_repository='github.com/steinwurf/external-boost-light.git',
        major_version=1))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='cpuid',
        git_repository='github.com/steinwurf/cpuid.git',
        major_version=3))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='fifi',
        git_repository='github.com/steinwurf/fifi.git',
        major_version=14))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='platform',
        git_repository='github.com/steinwurf/platform.git',
        major_version=1))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='sak',
        git_repository='github.com/steinwurf/sak.git',
        major_version=12))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='waf-tools',
        git_repository='github.com/steinwurf/external-waf-tools.git',
        major_version=2))

    opt.load("wurf_configure_output")
    opt.load('wurf_dependency_bundle')
    opt.load('wurf_tools')
    opt.load('python')


def configure(conf):

    if conf.is_toplevel():

        conf.load('wurf_dependency_bundle')
        conf.load('wurf_tools')

        conf.load_external_tool('mkspec', 'wurf_cxx_mkspec_tool')
        conf.load_external_tool('runners', 'wurf_runner')
        conf.load_external_tool('install_path', 'wurf_install_path')
        conf.load_external_tool('project_gen', 'wurf_project_generator')

        recurse_helper(conf, 'boost')
        recurse_helper(conf, 'cpuid')
        recurse_helper(conf, 'fifi')
        recurse_helper(conf, 'platform')
        recurse_helper(conf, 'sak')

    #Ensure that Python is configured properly
    if not conf.env['BUILD_PYTHON']:
        conf.fatal('Python was not configured properly')


def build(bld):
    # Remove NDEBUG which is added from conf.check_python_headers
    flag_to_remove = 'NDEBUG'
    defines = ['DEFINES_PYEMBED', 'DEFINES_PYEXT']
    for define in defines:
        while(flag_to_remove in bld.env[define]):
            bld.env[define].remove(flag_to_remove)

    bld.env['CFLAGS_PYEXT'] = []
    bld.env['CXXFLAGS_PYEXT'] = []

    CXX = bld.env.get_flat("CXX")
    # Matches both /usr/bin/g++ and /user/bin/clang++
    if 'g++' in CXX or 'clang' in CXX:
        bld.env.append_value('CXXFLAGS', '-fPIC')

    if bld.is_toplevel():

        bld.load('wurf_dependency_bundle')

        recurse_helper(bld, 'boost')
        recurse_helper(bld, 'cpuid')
        recurse_helper(bld, 'fifi')
        recurse_helper(bld, 'platform')
        recurse_helper(bld, 'sak')

    bld.recurse('src/fifi_python')


@feature('pyext')
@after_method('apply_link')
def test(self):
    if self.bld.has_tool_option('run_tests'):
        self.bld.add_post_fun(exec_test_python)


def exec_test_python(bld):
    python = bld.env['PYTHON'][0]
    env = dict(os.environ)
    env['PYTHONPATH'] = os.path.join(bld.out_dir, 'src', 'fifi_python')
    # First, run the unit tests in the 'test' folder
    if os.path.exists('test'):
        for f in sorted(os.listdir('test')):
            if f.endswith('.py'):
                test = os.path.join('test', f)
                bld.cmd_and_log('{0} {1}\n'.format(python, test), env=env)
    # Then run the examples in the 'examples' folder
    if os.path.exists('examples'):
        for f in sorted(os.listdir('examples')):
            if f.endswith('.py'):
                example = os.path.join('examples', f)
                bld.cmd_and_log('{0} {1}\n'.format(python, example), env=env)

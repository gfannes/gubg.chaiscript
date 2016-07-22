require(File.join(ENV['gubg'], 'shared'))
require('gubg/build/Executable')
require('gubg/build/Library')
include GUBG

task :default => :help
task :help do
    puts('declare: copy all headers to GUBG::shared')
    puts('define: build and copy libraries and executables to GUBG::shared')
end

task :clean do
    rm_rf '.cache'
end

task :declare do
    Dir.chdir(shared_dir('extern')) do
        git_clone('https://github.com/ChaiScript', 'ChaiScript') do
            publish('include', pattern: '**/*', dst: 'include')
        end
    end
end

task :define => :declare do
    chai = Build::Executable.new('chai')
    chai.add_include_path(shared_dir('include'))
    chai.add_sources(FileList.new('src/chai/**/*.cpp'))
    chai.add_library_path(shared_dir('lib'))
    chai.add_library('dl', 'pthread')
    chai.build
    publish(chai.name, dst: 'bin')
end

task :test => :define do
    Rake::Task['ut:test'].invoke
end

namespace :ut do
    ut = nil
    task :setup do
        ut = Build::Executable.new('unit_tests')
        ut.add_include_path(shared_dir('include'))
        ut.add_sources(FileList.new('src/test/**/*.cpp'))
        ut.add_sources(FileList.new(shared('include', '**/*.hpp')))
        ut.add_sources(shared_file('source', 'catch_runner.cpp'))
    end
    task :test => :setup do
        ut.build
        options = %w[-d yes -a]
        options << '[ut]'
        ut.run(options)
    end
end

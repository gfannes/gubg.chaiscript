require_relative("../gubg.build/bootstrap.rb")
require("gubg/shared")

task :prepare do
  Rake.sh("git submodule update --init --recursive") unless File.exist?("extern/ChaiScript/readme.md")
  Dir.chdir("extern/ChaiScript") do
    Rake.sh("git checkout release-6.x")
  end
end

task :uth
desc "Update to head: this is a manual operation now, develop is not stable enough"
task :uth_ => :prepare do
    Dir.chdir("extern/ChaiScript") do
        sh "git checkout develop"
        sh "git pull"
    end
end

task :run

task :clean

task :prepare

task :proper do
    rm_rf "extern"
end

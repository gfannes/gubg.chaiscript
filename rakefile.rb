require_relative("../gubg.build/bootstrap.rb")
require("gubg/shared")

task :prepare do
    Dir.chdir(GUBG.mkdir("extern")) do
        unless File.exist?("ChaiScript/readme.md")
            sh "git clone https://github.com/ChaiScript/ChaiScript"
            Dir.chdir("ChaiScript") do
                sh "git checkout release-6.x"
            end
        end
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

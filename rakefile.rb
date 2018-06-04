task :prepare do
    Dir.chdir("extern") do
        unless File.exist?("ChaiScript/readme.md")
            sh "git submodule update --init ChaiScript"
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

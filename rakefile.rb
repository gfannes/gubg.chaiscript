task :prepare do
    Dir.chdir("extern") do
        unless File.exist?("ChaiScript/readme.md")
            sh "git submodule update --init ChaiScript"
        end
    end
end

task :uth => :prepare do
    Dir.chdir("extern/ChaiScript") do
        sh "git checkout develop"
        sh "git pull"
    end
end

task :run

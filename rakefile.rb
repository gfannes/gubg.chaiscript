task :prepare do
    Dir.chdir("extern") do
        unless File.exist?("ChaiScript/readme.md")
            sh "git submodule update --init ChaiScript"
        end
        Dir.chdir("ChaiScript") do
            sh "git checkout develop"
            sh "git pull"
        end
    end
end

task :run

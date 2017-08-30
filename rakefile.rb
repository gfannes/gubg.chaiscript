task :prepare do
    Dir.chdir("extern") do
        unless File.exist?("ChaiScript/readme.md")
            sh "git submodule update --init ChaiScript"
        end
    end
end

task :run

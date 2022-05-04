here = File.dirname(__FILE__)

namespace :chaiscript do
	task :prepare do
		Dir.chdir(here) do
			sh "git submodule update --init --recursive"
		end
	end
	
	task :install do
		require("gubg/build/Cooker")
		cooker = GUBG::Build::Cooker.new().option("c++.std", 17).output("bin")

		recipes = %w[chai/exe]
		cooker.generate(:ninja, *recipes).ninja()
	end
end
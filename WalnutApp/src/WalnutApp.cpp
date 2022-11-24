#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include <iostream>
#include "windows.h"

// file
#include <filesystem>
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
#include <sstream>

class ExampleLayer : public Walnut::Layer
{
public:
	virtual void OnUIRender() override
	{
		static char str[16] = {"enter path"};
		
		ImGui::Begin("COPY");
		static char buf1[128] = ""; ImGui::InputText("Enter Copy Path", buf1, 128);
		// ImGui::ShowDemoWindow();
		
		// if (ImGui::Button("Copy")) {
		// 	std::string text = "TEST";
		// 	MessageBox(nullptr, TEXT(text), TEXT("Message"), MB_OK);
		// }
		static int clicked = 0;
		if (ImGui::Button("COPY"))
			clicked++;
		if (clicked & 1)
		{
			ImGui::SameLine();
			ImGui::Text(buf1);
			copyFile(buf1);
			clicked = 0;
		}
			
		ImGui::End();

		// ImGui::ShowDemoWindow();
	}
private:
	virtual void copyFile(std::string sourcePath) {
		std::string basePath = "I:\\tiok23yt\\shot\\";
		std::string runCommand = "";
		for (const auto& entry : recursive_directory_iterator(sourcePath))
			if (entry.path().extension().string() == ".mp4") {
				std::string fname = entry.path().stem().string();
				std::stringstream  data(fname);
				std::string line;
				std::vector<std::string> result = {};
				while(std::getline(data,line,'_'))
				{
					result.push_back(line); // Note: You may get a couple of blank lines
											// When multiple underscores are beside each other.
				}

				std::string destanation = basePath+result[0]+"\\"+result[1]+"\\"+result[2]+"\\04_comp\\finalimage\\02_anim\\"+entry.path().filename().string();
				
				std::ostringstream oss;
				oss << "xcopy " <<"\""<<entry.path().string() << "\"" << " " << destanation << "*" << " /Y"; // prevent space in source path
				std::string command = oss.str();
				system(command.c_str());
			}
		
	}
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "COPY";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}
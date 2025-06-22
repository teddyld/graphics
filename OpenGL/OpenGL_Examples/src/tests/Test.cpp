#include "Test.h"

namespace test {
	TestMenu::TestMenu(Test*& currentTestPointer)
		: m_CurrentTest(currentTestPointer)
	{
	}

	void TestMenu::OnImGuiRender()
	{
		std::string curr = "";
		for (auto& test : m_Tests)
		{
			if (curr != std::get<1>(test))
			{
				ImGui::Text(std::get<1>(test).c_str());
				ImGui::Separator();
				curr = std::get<1>(test);
			}

			if (ImGui::Button(std::get<0>(test).c_str()))
				m_CurrentTest = std::get<2>(test)();
		}
	}
}
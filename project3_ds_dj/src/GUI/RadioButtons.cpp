#include "GUI/RadioButtons.h"

RadioButtons::RadioButtons() 
	: m_currentIndex(0) { }

bool RadioButtons::processInput(XboxController &controller)
{
	if (!m_hasFocus || m_checkBoxes.size() == 0)
	{
		m_checkBoxes[m_currentIndex]->processInput(controller);
		m_checkBoxes[m_currentIndex]->demoteFocus();
		return false;
	}
	else
	{
		if (controller.isButtonPressed(XBOX360_UP))
		{
			if (m_up != nullptr)
			{
				m_up->promoteFocus();
				demoteFocus();
				m_checkBoxes[m_currentIndex]->demoteFocus();
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_DOWN))
		{
			if (m_down != nullptr)
			{
				m_down->promoteFocus();
				demoteFocus();
				m_checkBoxes[m_currentIndex]->demoteFocus();
				return true;
			}
		}

		// Cycle through radio buttons
		else if (controller.isButtonPressed(XBOX360_LEFT))
		{
			if (m_currentIndex > 0)
			{
				m_checkBoxes[m_currentIndex]->demoteFocus();
				m_currentIndex--;
				m_checkBoxes[m_currentIndex]->promoteFocus();
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_RIGHT))
		{
			if (m_currentIndex < m_checkBoxes.size() - 1)
			{
				m_checkBoxes[m_currentIndex]->demoteFocus();
				m_currentIndex++;
				m_checkBoxes[m_currentIndex]->promoteFocus();
				return true;
			}
		}

		////else if (controller.isButtonPressed(XBOX360_A))
		//{
		//	//std::cout << "A pressed RadioButtons" << std::endl;

		//	//for (unsigned int i = 0; i < m_checkBoxes.size(); i++)
		//	{
		//		//if (i == m_currentIndex)
		//			//continue;
		//		
		//		//m_checkBoxes[i]->demoteFocus();
		//	}
		//}

	}

	m_checkBoxes[m_currentIndex]->processInput(controller);
}

void RadioButtons::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (CheckBox *checkBox : m_checkBoxes)
		checkBox->draw(target, states);
}

void RadioButtons::add(CheckBox *button)
{
	m_checkBoxes.push_back(button);
}

void RadioButtons::promoteFocus()
{
	m_hasFocus = true;
	m_checkBoxes[m_currentIndex]->promoteFocus();
}
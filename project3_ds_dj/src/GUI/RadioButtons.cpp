#include "GUI/RadioButtons.h"

RadioButtons::RadioButtons() 
	: m_currentIndex(0) { }

bool RadioButtons::processInput(XboxController &controller)
{
	m_checkBoxes[m_currentIndex]->processInput(controller);

	if (!m_hasFocus || m_checkBoxes.size() == 0)
	{
		return false;
	}
	else
	{
		if (controller.isButtonPressed(XBOX360_UP))
		{
			if (m_up != nullptr)
			{
				m_up->promoteFocus(); // Set the button above *this to be in focus
				demoteFocus(); // Set the check box to be out of focus
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
			//if (m_checkBoxes[--m_currentIndex])
			{
				//m_currentIndex--;
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_RIGHT))
		{
			//if (m_checkBoxes[++m_currentIndex])
			{
				//m_currentIndex++;
				return true;
			}
		}
	}
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
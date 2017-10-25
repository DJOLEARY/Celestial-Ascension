#include "GUI/RadioButtons.h"

RadioButtons::RadioButtons() 
	: m_currentIndex(0) { }

bool RadioButtons::processInput(XboxController &controller)
{
	if (!m_hasFocus)
	{
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
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_DOWN))
		{
			if (m_down != nullptr)
			{
				m_down->promoteFocus();
				demoteFocus();
				return true;
			}
		}

		// Cycle through radio buttons
		else if (controller.isButtonPressed(XBOX360_LEFT))
		{
			if (m_currentIndex > 0)
			{
				buttons[m_currentIndex]->demoteFocus();
				m_currentIndex--;
				buttons[m_currentIndex]->promoteFocus();
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_RIGHT))
		{
			if (m_currentIndex < buttons.size() - 1)
			{
				buttons[m_currentIndex]->demoteFocus();
				m_currentIndex++;
				buttons[m_currentIndex]->promoteFocus();
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_A))
		{
			buttons[m_currentIndex]->toggle();

			for (size_t buttonIndex = 0; buttonIndex < buttons.size(); buttonIndex++)
			{
				if (m_currentIndex == buttonIndex)
					continue;

				buttons[buttonIndex]->turnOff();
			}
		}
	}
}

void RadioButtons::add(RadioButton *button)
{
	buttons.push_back(button);
}

void RadioButtons::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (RadioButton *rb : buttons)
	{
		rb->draw(target, states);
	}
}

void RadioButtons::promoteFocus()
{
	m_hasFocus = true;
	buttons[m_currentIndex]->promoteFocus();
}

void RadioButtons::demoteFocus()
{
	m_hasFocus = false;
	buttons[m_currentIndex]->demoteFocus();
}
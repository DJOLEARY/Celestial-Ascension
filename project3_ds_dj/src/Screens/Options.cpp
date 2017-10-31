#include "Screens\Options.h"

Options::Options()
	: Screen(GameState::Options), transitionIn(true)
{
	sf::Color focusIn(50, 200, 50);
	sf::Color focusOut(100, 20, 50);
	sf::Color fillColor(0, 0, 255);

	// Initiaise the GUI elements
	m_optionsTitle = new Label("Options", 80, sf::Vector2f(1920.0f / 2 - 400.0f, 100.0f), sf::Vector2f(1920.0f / 2, 100.0f));
	m_musicTitle = new Label("Music Volume", 24, sf::Vector2f(1920.0f / 2, 350), sf::Vector2f(1920.0f / 2 + 400.0f, 350));
	m_musicVolume = new Slider(focusIn, focusOut, fillColor, sf::Vector2f(1920.0f / 2, 400.0f), 
		200.0f, 20.0f, sf::Vector2f(1920.0f / 2 + 400.0f, 400.0f));
	m_effectsTitle = new Label("Effects Volume", 24, sf::Vector2f(1920 / 2, 450), sf::Vector2f(1920.0f / 2 + 400.0f, 450));
	m_effectsVolume = new Slider(focusIn, focusOut, fillColor, sf::Vector2f(1920.0f / 2, 500.0f),
		200.0f, 20.0f, sf::Vector2f(1920.0f / 2 + 400.0f, 500.0f));
	m_muteTitle = new Label("Mute", 24, sf::Vector2f(1920.0f / 2, 550), sf::Vector2f(1920.0f / 2 + 400.0f, 550));
	m_muteCheckBox = new CheckBox(sf::Vector2f(1920.0f / 2, 600), focusIn, focusOut, fillColor, 
		30.0f, 30.0f, sf::Vector2f(1920.0f / 2 + 400.0f, 600.0f));

	m_windowedLabel = new Label("Windowed", 24, sf::Vector2f(1920.0f / 2 - 75.0f, 650.0f), sf::Vector2f(1920.0f / 2 + 325.0f, 650.0f));
	m_windowStyleOptions.push_back(new RadioButton(focusIn, focusOut,fillColor, sf::Vector2f(1920.0f / 2 - 75.0f, 700.0f), 
		m_windowStyleOptions, sf::Vector2f(1920.0f / 2 + 325.0f, 700.0f), 22, 30.0f, 30.0f));

	m_fullscreenLabel = new Label("Fullscreen", 24, sf::Vector2f(1920.0f / 2 + 75.0f, 650.0f), sf::Vector2f(1920.0f / 2 + 475.0f, 650.0f));
	m_windowStyleOptions.push_back(new RadioButton(focusIn, focusOut, fillColor, sf::Vector2f(1920.0f / 2 + 75.0f, 700.0f),
		m_windowStyleOptions, sf::Vector2f(1920.0f / 2 + 475.0f, 700.0f), 22, 30.0f, 30.0f));

	if (!m_applyTexure.loadFromFile("Assets/GUI/ApplyButton.png"))
		std::cout << "ERROR::Options::ApplyButton image not loaded";

	// @refactor(darren): change order of end position for button
	m_applyButton = new Button(m_applyTexure, sf::Vector2f(1920.0f / 2, 800.0f), focusIn, focusOut,
		1.0f, 1.0f, sf::Vector2f(1920.0f / 2 + 400.0f, 800.0f));

	// Set the first UI element the user has control over to the volume
	m_musicVolume->promoteFocus();

	// Assingn call back function here
	m_musicVolume->increase = std::bind(&Options::volumeUpSliderMusic, this);
	m_musicVolume->decrease = std::bind(&Options::volumeDownSliderMusic, this);

	m_musicVolume->m_down = m_effectsVolume;
	m_effectsVolume->m_down = m_muteCheckBox;
	m_effectsVolume->m_up = m_musicVolume;
	m_muteCheckBox->m_down = m_windowStyleOptions[0];
	m_muteCheckBox->m_up = m_effectsVolume;
	m_windowStyleOptions[0]->m_up = m_muteCheckBox;
	m_windowStyleOptions[1]->m_up = m_muteCheckBox;
	m_windowStyleOptions[0]->m_down = m_applyButton;
	m_windowStyleOptions[1]->m_down = m_applyButton;
	m_windowStyleOptions[0]->m_right = m_windowStyleOptions[1];
	m_windowStyleOptions[1]->m_left = m_windowStyleOptions[0];
	m_applyButton->m_up = m_windowStyleOptions[0];

	m_gui.add(m_optionsTitle);
	m_gui.add(m_musicTitle);
	m_gui.add(m_musicVolume);
	m_gui.add(m_effectsTitle);
	m_gui.add(m_effectsVolume);
	m_gui.add(m_muteTitle);
	m_gui.add(m_muteCheckBox);
	for (RadioButton *windowOpt : m_windowStyleOptions)
		m_gui.add(windowOpt);
	m_gui.add(m_windowedLabel);
	m_gui.add(m_fullscreenLabel);
	m_gui.add(m_applyButton);

	m_gui.setWidgetsAlpha(0.0f);
}

/// <summary>
/// function resets the Options Screen after the game state has been changed
/// </summary>
void Options::reset()
{
	// Reset the top Gui elements to be in focus
	m_musicVolume->promoteFocus();
	transitionIn = true;
	interpolation = 0.0f;
	m_applyButtonPressed = false;
}

/// <summary>
/// update function processes input for the options screen
/// </summary>
/// <param name="controller">controller used for processing input</param>
void Options::update(XboxController &controller)
{
	m_gui.processInput(controller);

	if (controller.isButtonPressed(XBOX360_B))
	{
		m_applyButtonPressed = true;
	}

	if (m_applyButtonPressed)
	{
		m_gui.transitionOut(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			m_nextGameState = GameState::MainMenu;
			reset();
		}
	}

	if (transitionIn)
	{
		m_gui.transitionIn(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			interpolation = 0.0f;
			transitionIn = false;
		}
	}
}

/// <summary>
/// Function linked to a callback function for thhe volume music slider
/// </summary>
void Options::volumeUpSliderMusic()
{

}

/// <summary>
///  Function linked to a callback function for thhe volume music slider
/// </summary>
void Options::volumeDownSliderMusic()
{
	
}

/// <summary>
///  Function linked to a callback function for thhe volume effects slider
/// </summary>
void Options::volumeUpSliderEffects()
{
	
}

/// <summary>
///  Function linked to a callback function for thhe volume effects slider
/// </summary>
void Options::volumeDownSliderEffects()
{
	
}

/// <summary>
/// Function linked to a callback function for the apply button
/// </summary>
void Options::applyButtonSelected()
{
	m_applyButtonPressed = true;
	m_applyButton->demoteFocus();
}

/// <summary>
/// Function linked to a callback function for the mute check box
/// </summary>
void Options::checkBoxSwitched()
{
	
}

/// <summary>
/// Function used for determining the starting positions for each RGB
/// when the colour radio buttons are interacted with
/// </summary>
void Options::setColorSliders()
{
	
}

/// <summary>
/// Function determines which RGB value of which colour should be changed
/// </summary>
void Options::setColor()
{
	
}

/// <summary>
/// Function is linked to the call back functions for the difficulty
/// radio buttons
/// </summary>
void Options::changeDifficulty()
{
	
}
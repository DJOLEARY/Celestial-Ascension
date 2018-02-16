#include "Screens\Options.h"

Options::Options(sf::View &view, sf::Music *music, sf::Sound *confirmSound, sf::Sound *shotSound, 
	sf::Sound *waveCompleteSound, sf::Sound *m_shieldSound, sf::Sound *m_doubleBulletSound, sf::Sound *m_heartSound, 
	sf::Sound *deathSound, sf::Sound *turretShotSound, sf::Sound *hitWallSound, sf::Sound *navigateSound, sf::Sound *backButton):
	Screen(GameState::Options, view), 
	transitionIn(true),
	m_music(music),
	m_confirmSound(confirmSound),
	m_shieldSound(m_shieldSound),
	m_doubleBulletSound(m_doubleBulletSound),
	m_heartSound(m_heartSound),
	m_waveCompleteSound(waveCompleteSound),
	m_deathSound(deathSound),
	m_turretShotSound(turretShotSound),
	m_hitWallSound(hitWallSound),
	m_navigateSound(navigateSound),
	m_backSound(backButton)
{
	sf::Color focusIn(50, 200, 50);
	sf::Color focusOut(100, 20, 50);
	sf::Color fillColor(178, 85, 23);

	// Initiaise the GUI elements
	m_optionsTitle = new Label("Options", 80, sf::Vector2f(1920.0f / 2 - 400.0f, 200.0f), sf::Vector2f(1920.0f / 2, 200.0f));
	m_musicTitle = new Label("Music Volume", 24, sf::Vector2f(1920.0f / 2, 350), sf::Vector2f(1920.0f / 2 + 400.0f, 350));
	m_musicVolume = new Slider(m_navigateSound, focusIn, focusOut, fillColor, sf::Vector2f(1920.0f / 2, 400.0f), 
		200.0f, 20.0f, sf::Vector2f(1920.0f / 2 + 400.0f, 400.0f));
	m_effectsTitle = new Label("Effects Volume", 24, sf::Vector2f(1920 / 2, 450), sf::Vector2f(1920.0f / 2 + 400.0f, 450));
	m_effectsVolume = new Slider(m_navigateSound, focusIn, focusOut, fillColor, sf::Vector2f(1920.0f / 2, 500.0f),
		200.0f, 20.0f, sf::Vector2f(1920.0f / 2 + 400.0f, 500.0f));
	m_muteTitle = new Label("Mute", 24, sf::Vector2f(1920.0f / 2, 550), sf::Vector2f(1920.0f / 2 + 400.0f, 550));
	m_muteCheckBox = new CheckBox(m_confirmSound, m_navigateSound, sf::Vector2f(1920.0f / 2, 600), focusIn, focusOut, fillColor,
		30.0f, 30.0f, sf::Vector2f(1920.0f / 2 + 400.0f, 600.0f));

	m_windowedLabel = new Label("Windowed", 24, sf::Vector2f(1920.0f / 2 - 75.0f, 650.0f), sf::Vector2f(1920.0f / 2 + 325.0f, 650.0f));
	m_windowStyleOptions.push_back(new RadioButton(focusIn, focusOut,fillColor, sf::Vector2f(1920.0f / 2 - 75.0f, 700.0f), 
		m_windowStyleOptions, sf::Vector2f(1920.0f / 2 + 325.0f, 700.0f), 22, 30.0f, 30.0f));

	m_fullscreenLabel = new Label("Fullscreen", 24, sf::Vector2f(1920.0f / 2 + 75.0f, 650.0f), sf::Vector2f(1920.0f / 2 + 475.0f, 650.0f));
	m_windowStyleOptions.push_back(new RadioButton(focusIn, focusOut, fillColor, sf::Vector2f(1920.0f / 2 + 75.0f, 700.0f),
		m_windowStyleOptions, sf::Vector2f(1920.0f / 2 + 475.0f, 700.0f), 22, 30.0f, 30.0f));

	// Set the first UI element the user has control over to the volume
	m_musicVolume->promoteFocus();

	// Assingn call back function here
	m_musicVolume->increase = std::bind(&Options::volumeChangeSliderMusic, this);
	m_musicVolume->decrease = std::bind(&Options::volumeChangeSliderMusic, this);
	m_effectsVolume->increase = std::bind(&Options::volumeChangeSliderEffects, this);
	m_effectsVolume->decrease = std::bind(&Options::volumeChangeSliderEffects, this);
	m_muteCheckBox->select = std::bind(&Options::checkBoxSwitched, this);
	m_windowStyleOptions[0]->select = std::bind(&Options::windowedSelected, this);
	m_windowStyleOptions[1]->select = std::bind(&Options::fullscreenSelected, this);

	m_musicVolume->m_down = m_effectsVolume;
	m_effectsVolume->m_down = m_muteCheckBox;
	m_effectsVolume->m_up = m_musicVolume;
	m_muteCheckBox->m_down = m_windowStyleOptions[0];
	m_muteCheckBox->m_up = m_effectsVolume;
	m_windowStyleOptions[0]->activate();
	m_windowStyleOptions[0]->m_up = m_muteCheckBox;
	m_windowStyleOptions[1]->m_up = m_muteCheckBox;
	m_windowStyleOptions[0]->m_right = m_windowStyleOptions[1];
	m_windowStyleOptions[1]->m_left = m_windowStyleOptions[0];

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

	m_gui.setWidgetsAlpha(0.0f);

	//----Set All Sounds Volumes Here----//
	m_music->pause();
	//m_confirmSound->setVolume(0);
	//m_shotSound->setVolume(0);
	//m_waveCompleteSound->setVolume(0);
	//m_pickUpSound->setVolume(0);
	//m_deathSound->setVolume(0);
	//m_turretShotSound->setVolume(0);
	//m_hitWallSound->setVolume(0);
	//m_navigateSound->setVolume(0);
}

/// <summary>
/// function resets the Options Screen after the game state has been changed
/// </summary>
void Options::reset()
{
	// Reset the top Gui elements to be in focus
	transitionIn = true;
	interpolation = 0.0f;
	m_backButtonPressed = false;

	for (Widget *widget : m_gui.m_widgets)
		widget->demoteFocus();

	m_musicVolume->promoteFocus();
}

/// <summary>
/// update function processes input for the options screen
/// </summary>
/// <param name="controller">controller used for processing input</param>
void Options::update(XboxController &controller, sf::Int32 dt)
{
	if (controller.isButtonPressed(XBOX360_B))
	{
		m_backButtonPressed = true;
		m_backSound->play();
	}

	m_gui.processInput(controller);

	if (m_backButtonPressed)
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
/// Function linked to a callback function for the volume music slider
/// </summary>
void Options::volumeChangeSliderMusic()
{
	m_musicVolumeValue = m_musicVolume->getPercentageFull();

	//----Set All Sounds Volumes Here----//
	m_music->setVolume(m_musicVolumeValue);
}

/// <summary>
///  Function linked to a callback function for the volume effects slider
/// </summary>
void Options::volumeChangeSliderEffects()
{
	m_effectsVolumeValue = m_effectsVolume->getPercentageFull();

	//----Set All Sounds Volumes Here----//
	m_confirmSound->setVolume(m_effectsVolumeValue);
	m_shotSound->setVolume(m_effectsVolumeValue / 4);
	m_waveCompleteSound->setVolume(m_effectsVolumeValue);
	m_shieldSound->setVolume(m_effectsVolumeValue);
	m_doubleBulletSound->setVolume(m_effectsVolumeValue);
	m_heartSound->setVolume(m_effectsVolumeValue);
	m_deathSound->setVolume(m_effectsVolumeValue);
	m_turretShotSound->setVolume(m_effectsVolumeValue);
	m_hitWallSound->setVolume(m_effectsVolumeValue);
	m_navigateSound->setVolume(m_effectsVolumeValue);
}

/// <summary>
/// Function linked to a callback function for the back button
/// </summary>
void Options::backButtonSelected()
{
	m_backButtonPressed = true;
	//m_confirmSound->play();
	m_backSound->play();
}

/// <summary>
/// Function linked to a callback function for the mute check box
/// </summary>
void Options::checkBoxSwitched()
{
	if (m_muted == true)
	{
		m_muted = false;

		//----Set All Sounds Volumes Here----//
		m_music->play();
		m_confirmSound->setVolume(m_effectsVolumeValue);
		m_shotSound->setVolume(m_effectsVolumeValue / 4);
		m_waveCompleteSound->setVolume(m_effectsVolumeValue);
		m_shieldSound->setVolume(m_effectsVolumeValue);
		m_doubleBulletSound->setVolume(m_effectsVolumeValue);
		m_heartSound->setVolume(m_effectsVolumeValue);
		m_deathSound->setVolume(m_effectsVolumeValue);
		m_turretShotSound->setVolume(m_effectsVolumeValue);
		m_hitWallSound->setVolume(m_effectsVolumeValue);
		m_navigateSound->setVolume(m_effectsVolumeValue);

		m_confirmSound->play();
	}
	else if (m_muted == false)
	{
		m_muted = true;

		//----Set All Sounds Volumes Here----//
		m_music->pause();
		m_confirmSound->setVolume(0);
		m_shotSound->setVolume(0);
		m_waveCompleteSound->setVolume(0);
		m_shieldSound->setVolume(0);
		m_doubleBulletSound->setVolume(0);
		m_heartSound->setVolume(0);
		m_deathSound->setVolume(0);
		m_turretShotSound->setVolume(0);
		m_hitWallSound->setVolume(0);
		m_navigateSound->setVolume(0);
	}
}

void Options::windowedSelected()
{
	if (m_windowStyleOptions[0]->getState() == true)
		m_goToWindowedMode = true;
	m_confirmSound->play();
}

void Options::fullscreenSelected()
{
	if(m_windowStyleOptions[1]->getState() == true)
		m_goToFullscreenMode = true;
	m_confirmSound->play();
}
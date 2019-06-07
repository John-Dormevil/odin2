/*
  ==============================================================================

    PhaserComponent.h
    Created: 27 Feb 2019 12:02:15am
    Author:  frot

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "GlobalIncludes.h"
#include "Knob.h"
#include "OdinButton.h"
#include "SyncTimeSelector.h"


#define AMOUNT_POS_X 103
#define AMOUNT_POS_Y 43
#define FREQ_POS_X 31
#define FREQ_POS_Y 17
#define DRY_WET_POS_X 175
#define DRY_WET_POS_Y (FREQ_POS_Y)
#define FX_SYNC_POS_X 37
#define FX_SYNC_POS_Y 79
#define FX_RESET_POS_X 176
#define FX_RESET_POS_Y FX_SYNC_POS_Y
#define SYNC_TIME_FX_POS_X 16
#define SYNC_TIME_FX_POS_Y 35

#define FX_FREQ_MIN 0.05
#define FX_FREQ_MAX 20
#define FX_FREQ_MID 0.8
#define FX_FREQ_DEFAULT 1
#define FX_AMOUNT_DEFAULT 0.3

#define FX_DRYWET_DEFAULT 1

#define PHASER_SYNC_TIME_POS_X 0
#define PHASER_SYNC_TIME_POS_Y 41
#define PHASER_SYNC_POS_X 20
#define PHASER_SYNC_POS_Y 73
#define PHASER_RESET_POS_X 70
#define PHASER_RESET_POS_Y PHASER_SYNC_POS_Y
#define PHASER_RATE_POS_X 15 + 61*0
#define PHASER_RATE_POS_Y 11
#define PHASER_MOD_POS_X  15 + 61 * 1 
#define PHASER_MOD_POS_Y PHASER_RATE_POS_Y
#define PHASER_FREQ_POS_X 15 + 61 * 2
#define PHASER_FREQ_POS_Y PHASER_RATE_POS_Y
#define phaser_feedback_POS_X PHASER_FREQ_POS_X
#define phaser_feedback_POS_Y 60
#define PHASER_DRY_WET_POS_X 190
#define PHASER_DRY_WET_POS_Y 36

//==============================================================================
/*
 */
class PhaserComponent : public Component {
public:
  PhaserComponent(AudioProcessorValueTreeState &vts, std::string p_fx_name,
                  bool p_is_standalone);
  ~PhaserComponent();

  void forceValueTreeOntoComponents(ValueTree p_tree);

  void paint(Graphics &) override;
  void resized() override;

  void setSyncTimeColor(juce::Colour p_color) { m_sync_time.setColor(p_color); }

  void setImage(juce::Image p_background, bool p_sync) {
    if (p_sync) {
      m_background_sync = p_background;
    } else {
      m_background_no_sync = p_background;
    }
  }

  void setSyncEnabled(bool p_sync);

private:
  bool m_is_standalone_plugin;

  Knob m_rate;
  Knob m_mod;
  Knob m_freq;
  Knob m_feedback;
  Knob m_dry_wet;

  OdinButton m_sync;
  OdinButton m_reset;

  juce::Image m_background_sync;
  juce::Image m_background_no_sync;

  SyncTimeSelector m_sync_time;

  bool m_sync_enabled = false;

  std::string m_fx_name;
  AudioProcessorValueTreeState &m_value_tree;

  std::unique_ptr<SliderAttachment> m_rate_attach;
  std::unique_ptr<SliderAttachment> m_feedback_attach;
  std::unique_ptr<SliderAttachment> m_freq_attach;
  std::unique_ptr<SliderAttachment> m_mod_attach;
  std::unique_ptr<SliderAttachment> m_drywet_attach;

  std::unique_ptr<ButtonAttachment> m_sync_attach;
  std::unique_ptr<ButtonAttachment> m_reset_attach;

  Identifier m_fx_synctime_numerator_identifier;
  Identifier m_fx_synctime_denominator_identifier;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhaserComponent)
};

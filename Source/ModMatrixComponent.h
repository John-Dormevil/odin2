/*
  ==============================================================================

    ModMatrixComponent.h
    Created: 27 Feb 2019 1:27:55am
    Author:  frot

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "GlasDropdown.h"
#include "GlobalIncludes.h"
#include "ModAmountComponent.h"

#define N_ROWS 9

//==============================================================================
/*
 */
class ModMatrixComponent : public Component {
public:
  ModMatrixComponent(AudioProcessorValueTreeState& vts);
  ~ModMatrixComponent();

  void paint(Graphics &) override;
  void resized() override;

  std::function<void(int&, int&, int&, int&, int&, int&)> getOscFilterTypes = [](int&, int&, int&, int&, int&, int&){};

private:
  void clearRow(int p_row);

  void createMenu(PopupMenu* p_menu);
  void setStandardMenu(PopupMenu *p_menu);

  GlasDropdown m_source[N_ROWS];
  ModAmountComponent m_amount_1[N_ROWS];
  GlasDropdown m_dest_1[N_ROWS];
  ModAmountComponent m_amount_2[N_ROWS];
  GlasDropdown m_dest_2[N_ROWS];
  ModAmountComponent m_amount_3[N_ROWS];
  GlasDropdown m_scale[N_ROWS];

//  Identifier m_source_identifier;
//  Identifier m_dest_1_identifier;
//  Identifier m_dest_2_identifier;
//  Identifier m_scale_identifier;

  //std::unique_ptr<ComboBoxAttachment> m_source_attach[N_ROWS];
  //std::unique_ptr<ComboBoxAttachment> m_dest_1_attach[N_ROWS];
  //std::unique_ptr<ComboBoxAttachment> m_dest_2_attach[N_ROWS];
  //std::unique_ptr<ComboBoxAttachment> m_scale_attach[N_ROWS];

  Identifier m_source_identifier0;
  Identifier m_source_identifier1;
  Identifier m_source_identifier2;
  Identifier m_source_identifier3;
  Identifier m_source_identifier4;
  Identifier m_source_identifier5;
  Identifier m_source_identifier6;
  Identifier m_source_identifier7;
  Identifier m_source_identifier8;

  Identifier m_dest_1_identifier0;
  Identifier m_dest_1_identifier1;
  Identifier m_dest_1_identifier2;
  Identifier m_dest_1_identifier3;
  Identifier m_dest_1_identifier4;
  Identifier m_dest_1_identifier5;
  Identifier m_dest_1_identifier6;
  Identifier m_dest_1_identifier7;
  Identifier m_dest_1_identifier8;

  Identifier m_dest_2_identifier0;
  Identifier m_dest_2_identifier1;
  Identifier m_dest_2_identifier2;
  Identifier m_dest_2_identifier3;
  Identifier m_dest_2_identifier4;
  Identifier m_dest_2_identifier5;
  Identifier m_dest_2_identifier6;
  Identifier m_dest_2_identifier7;
  Identifier m_dest_2_identifier8;

  Identifier m_scale_identifier0;
  Identifier m_scale_identifier1;
  Identifier m_scale_identifier2;
  Identifier m_scale_identifier3;
  Identifier m_scale_identifier4;
  Identifier m_scale_identifier5;
  Identifier m_scale_identifier6;
  Identifier m_scale_identifier7;
  Identifier m_scale_identifier8;

  Identifier m_amount_1_identifier0;
  Identifier m_amount_2_identifier0;
  Identifier m_amount_3_identifier0;
  Identifier m_amount_1_identifier1;
  Identifier m_amount_2_identifier1;
  Identifier m_amount_3_identifier1;
  Identifier m_amount_1_identifier2;
  Identifier m_amount_2_identifier2;
  Identifier m_amount_3_identifier2;
  Identifier m_amount_1_identifier3;
  Identifier m_amount_2_identifier3;
  Identifier m_amount_3_identifier3;
  Identifier m_amount_1_identifier4;
  Identifier m_amount_2_identifier4;
  Identifier m_amount_3_identifier4;
  Identifier m_amount_1_identifier5;
  Identifier m_amount_2_identifier5;
  Identifier m_amount_3_identifier5;
  Identifier m_amount_1_identifier6;
  Identifier m_amount_2_identifier6;
  Identifier m_amount_3_identifier6;
  Identifier m_amount_1_identifier7;
  Identifier m_amount_2_identifier7;
  Identifier m_amount_3_identifier7;
  Identifier m_amount_1_identifier8;
  Identifier m_amount_2_identifier8;
  Identifier m_amount_3_identifier8;

  // can't be array due to missing standard constructor..
  juce::DrawableButton m_clear_button0;
  juce::DrawableButton m_clear_button1;
  juce::DrawableButton m_clear_button2;
  juce::DrawableButton m_clear_button3;
  juce::DrawableButton m_clear_button4;
  juce::DrawableButton m_clear_button5;
  juce::DrawableButton m_clear_button6;
  juce::DrawableButton m_clear_button7;
  juce::DrawableButton m_clear_button8;

  AudioProcessorValueTreeState &m_value_tree;

  PopupMenu m_analog_osc_menu[3];
  PopupMenu m_wavetable_osc_menu[3];
  PopupMenu m_multi_osc_menu[3];
  PopupMenu m_vector_osc_menu[3];
  PopupMenu m_fm_osc_menu[3];
  PopupMenu m_noise_osc_menu[3];
  PopupMenu m_draw_osc_menu[3];
  PopupMenu m_chiptune_osc_menu[3];
  PopupMenu m_standard_fil_menu[3];
  PopupMenu m_SEM_fil_menu[3];
  PopupMenu m_comb_fil_menu[3];
  PopupMenu m_formant_fil_menu[3];
  PopupMenu m_adsr_menu[4];
  PopupMenu m_lfo_menu[4];
  PopupMenu m_amp_menu;
  PopupMenu m_distortion_menu;
  PopupMenu m_delay_menu;
  PopupMenu m_phaser_menu;
  PopupMenu m_flanger_menu;
  PopupMenu m_chorus_menu;

  PopupMenu m_sources_menu;

  

  int m_panel_height;
  int m_small_panel_width;
  int m_big_panel_width;

  juce::Colour m_color;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModMatrixComponent)
};

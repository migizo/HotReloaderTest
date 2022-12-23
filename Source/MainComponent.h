#pragma once

#include <JuceHeader.h>

//==============================================================================
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    std::unique_ptr<HotReloader> fileHotReloader;
    std::unique_ptr<HotReloader> folderHotReloader;

    juce::TextEditor fileTextView;
    juce::OwnedArray<juce::TextEditor> folderFileTextView;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

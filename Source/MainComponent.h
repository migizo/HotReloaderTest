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
    // Resources/sample.txt
    std::unique_ptr<HotReloader> fileHotReloader;
    juce::TextEditor fileTextView;

    // Resources/sampleFolderフォルダ
    void resetFolderViewBounds(juce::Rectangle<int> area);
    std::unique_ptr<HotReloader> folderHotReloader;
    juce::OwnedArray<juce::TextEditor> folderFileTextView;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

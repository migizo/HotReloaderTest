#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    juce::File rsrcDir = juce::File::getSpecialLocation(juce::File::SpecialLocationType::currentApplicationFile).getChildFile("Contents/Resources");
    
    //------------------------------------------
    // Resources/sample.txt
    //------------------------------------------
    addAndMakeVisible(fileTextView);
    fileTextView.setMultiLine(true);
    fileTextView.setReadOnly(true);
    
    auto fileReloadCallback = [this](const juce::File& file)
    {
        fileTextView.setText(file.loadFileAsString());
    };
    fileHotReloader.reset(new HotReloader(rsrcDir.getChildFile("sample.txt"), fileReloadCallback));
    
    //------------------------------------------
    // Resources/sampleFolderフォルダ
    //------------------------------------------
    auto folderReloadCallback = [this](const juce::File& folder)
    {
        juce::Array<juce::File> fileList = folder.findChildFiles(juce::File::TypesOfFileToFind::findFiles, true);

        folderFileTextView.clear();
        for (auto& f: fileList)
        {
            auto* textView = new juce::TextEditor();
            addAndMakeVisible(textView);
            textView->setMultiLine(true);
            textView->setReadOnly(true);
            textView->setText(f.loadFileAsString());
            folderFileTextView.add(textView);
        }
        
        auto area = getLocalBounds();
        area.removeFromTop(80);
        resetFolderViewBounds(area);
    };
    folderHotReloader.reset(new HotReloader(rsrcDir.getChildFile("sampleFolder"), folderReloadCallback));
    
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    fileTextView.setBounds(area.removeFromTop(80));
    resetFolderViewBounds(area);
}

//==============================================================================
void MainComponent::resetFolderViewBounds(juce::Rectangle<int> area)
{
    area.removeFromLeft(20);
    for (auto* const textView : folderFileTextView)
    {
        textView->setBounds(area.removeFromTop(80));
    }
}

//draw.cpp

#include "TColor.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TGSplitter.h"
#include "TG3DLine.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TArrow.h"

#include <vector>
#include <cstdlib>

#include "hivapParameter.h"
#include "iostream"


bool SortAFER(const CrossSectionExp &a, const CrossSectionExp &b) 
{
    return a.AFER < b.AFER;
}
bool SortAFusion(const CrossSectionExp &a, const CrossSectionExp &b) 
{
    return (a.Ap + a.At) < (b.Ap + b.At);
}

hivapParameter::hivapParameter(const TGWindow * p, const TGWindow * main, char *name)
{
	SetCleanup(kDeepCleanup);
	SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	ngraph_Draw = 0;

	HivapParameterFrame = new TGVerticalFrame(this, 800, 1500);
	AddFrame(HivapParameterFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 10, 10, 5, 5));
	HivapParameterFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	TGHSplitter *hsplitter0 = new TGHSplitter(HivapParameterFrame,200,2);
	HivapParameterFrame->AddFrame(hsplitter0, new TGLayoutHints(kLHintsTop | kLHintsExpandX,0,0,10,10));

	FusionFrame = new TGHorizontalFrame(HivapParameterFrame, 800, 80);
	HivapParameterFrame->AddFrame(FusionFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	FusionFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));

	FusionNameFrame = new TGVerticalFrame(FusionFrame, 150, 80);
	FusionFrame->AddFrame(FusionNameFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	FusionNameFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	FusionNameText = new TGTextEntry(FusionNameFrame, new TGTextBuffer(100), 10000);
	FusionNameText->SetText("Fusion : ");
	FusionNameFrame->AddFrame(FusionNameText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	FusionNameText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	FusionNameText->Resize(150, 80);
	FusionNameText->SetEnabled(kFALSE);
	FusionNameText->SetFrameDrawn(kFALSE);
	FusionNameText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	FusionNameText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	FusionInformationFrame = new TGVerticalFrame(FusionFrame, 650, 80);
	FusionFrame->AddFrame(FusionInformationFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	FusionInformationFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	
	FusionMinFrame = new TGHorizontalFrame(FusionInformationFrame, 650, 40);
	FusionInformationFrame->AddFrame(FusionMinFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	FusionMinFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	
	FusionMinZText = new TGTextEntry(FusionMinFrame, new TGTextBuffer(100), 10000);
	FusionMinZText->SetText("Z(min) = ");
	FusionMinFrame->AddFrame(FusionMinZText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	FusionMinZText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	FusionMinZText->SetAlignment(kTextCenterX);
	FusionMinZText->Resize(200, 40);
	FusionMinZText->SetEnabled(kFALSE);
	FusionMinZText->SetFrameDrawn(kFALSE);
	FusionMinZText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	FusionMinZText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	FusionMinZNumber = new TGNumberEntry(FusionMinFrame, 0, 0, TGNumberFormat::kNESInteger);
	FusionMinFrame->AddFrame(FusionMinZNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	FusionMinZNumber->GetButtonUp()->ChangeOptions(FusionMinZNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	FusionMinZNumber->GetButtonDown()->ChangeOptions(FusionMinZNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	FusionMinZNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	FusionMinZNumber->Resize(100, 40);
	FusionMinZNumber->SetNumber(83);
	FusionMinZNumber->Associate(this);

	FusionMinAText = new TGTextEntry(FusionMinFrame, new TGTextBuffer(100), 10000);
	FusionMinAText->SetText("A(min) = ");
	FusionMinFrame->AddFrame(FusionMinAText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	FusionMinAText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	FusionMinAText->SetAlignment(kTextCenterX);
	FusionMinAText->Resize(200, 40);
	FusionMinAText->SetEnabled(kFALSE);
	FusionMinAText->SetFrameDrawn(kFALSE);
	FusionMinAText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	FusionMinAText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	FusionMinANumber = new TGNumberEntry(FusionMinFrame, 0, 0, TGNumberFormat::kNESInteger);
	FusionMinFrame->AddFrame(FusionMinANumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	FusionMinANumber->GetButtonUp()->ChangeOptions(FusionMinANumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	FusionMinANumber->GetButtonDown()->ChangeOptions(FusionMinANumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	FusionMinANumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	FusionMinANumber->Resize(100, 40);
	FusionMinANumber->SetNumber(187);
	FusionMinANumber->Associate(this);

	FusionMinNText = new TGTextEntry(FusionMinFrame, new TGTextBuffer(100), 10000);
	FusionMinNText->SetText("N(min) = ");
	FusionMinFrame->AddFrame(FusionMinNText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	FusionMinNText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	FusionMinNText->SetAlignment(kTextCenterX);
	FusionMinNText->Resize(190, 40);
	FusionMinNText->SetEnabled(kFALSE);
	FusionMinNText->SetFrameDrawn(kFALSE);
	FusionMinNText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	FusionMinNText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	FusionMinNNumber = new TGNumberEntry(FusionMinFrame, 0, 0, TGNumberFormat::kNESInteger);
	FusionMinFrame->AddFrame(FusionMinNNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	FusionMinNNumber->GetButtonUp()->ChangeOptions(FusionMinNNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	FusionMinNNumber->GetButtonDown()->ChangeOptions(FusionMinNNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	FusionMinNNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	FusionMinNNumber->Resize(100, 40);
	FusionMinNNumber->SetNumber(104);
	FusionMinNNumber->Associate(this);
	
	FusionMaxFrame = new TGHorizontalFrame(FusionInformationFrame, 800, 40);
	FusionInformationFrame->AddFrame(FusionMaxFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	FusionMaxFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));

	FusionMaxZText = new TGTextEntry(FusionMaxFrame, new TGTextBuffer(100), 10000);
	FusionMaxZText->SetText("Z(max) = ");
	FusionMaxFrame->AddFrame(FusionMaxZText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	FusionMaxZText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	FusionMaxZText->SetAlignment(kTextCenterX);
	FusionMaxZText->Resize(200, 40);
	FusionMaxZText->SetEnabled(kFALSE);
	FusionMaxZText->SetFrameDrawn(kFALSE);
	FusionMaxZText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	FusionMaxZText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	FusionMaxZNumber = new TGNumberEntry(FusionMaxFrame, 0, 0, TGNumberFormat::kNESInteger);
	FusionMaxFrame->AddFrame(FusionMaxZNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	FusionMaxZNumber->GetButtonUp()->ChangeOptions(FusionMaxZNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	FusionMaxZNumber->GetButtonDown()->ChangeOptions(FusionMaxZNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	FusionMaxZNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	FusionMaxZNumber->Resize(100, 40);
	FusionMaxZNumber->SetNumber(83);
	FusionMaxZNumber->Associate(this);

	FusionMaxAText = new TGTextEntry(FusionMaxFrame, new TGTextBuffer(100), 10000);
	FusionMaxAText->SetText("A(max) = ");
	FusionMaxFrame->AddFrame(FusionMaxAText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	FusionMaxAText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	FusionMaxAText->SetAlignment(kTextCenterX);
	FusionMaxAText->Resize(200, 40);
	FusionMaxAText->SetEnabled(kFALSE);
	FusionMaxAText->SetFrameDrawn(kFALSE);
	FusionMaxAText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	FusionMaxAText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	FusionMaxANumber = new TGNumberEntry(FusionMaxFrame, 0, 0, TGNumberFormat::kNESInteger);
	FusionMaxFrame->AddFrame(FusionMaxANumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	FusionMaxANumber->GetButtonUp()->ChangeOptions(FusionMaxANumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	FusionMaxANumber->GetButtonDown()->ChangeOptions(FusionMaxANumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	FusionMaxANumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	FusionMaxANumber->Resize(100, 40);
	FusionMaxANumber->SetNumber(187);
	FusionMaxANumber->Associate(this);

	FusionMaxNText = new TGTextEntry(FusionMaxFrame, new TGTextBuffer(100), 10000);
	FusionMaxNText->SetText("N(Max) = ");
	FusionMaxFrame->AddFrame(FusionMaxNText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	FusionMaxNText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	FusionMaxNText->SetAlignment(kTextCenterX);
	FusionMaxNText->Resize(190, 40);
	FusionMaxNText->SetEnabled(kFALSE);
	FusionMaxNText->SetFrameDrawn(kFALSE);
	FusionMaxNText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	FusionMaxNText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	FusionMaxNNumber = new TGNumberEntry(FusionMaxFrame, 0, 0, TGNumberFormat::kNESInteger);
	FusionMaxFrame->AddFrame(FusionMaxNNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	FusionMaxNNumber->GetButtonUp()->ChangeOptions(FusionMaxNNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	FusionMaxNNumber->GetButtonDown()->ChangeOptions(FusionMaxNNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	FusionMaxNNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	FusionMaxNNumber->Resize(100, 40);
	FusionMaxNNumber->SetNumber(104);
	FusionMaxNNumber->Associate(this);

	TGHSplitter *hsplitter1 = new TGHSplitter(HivapParameterFrame,800,2);
	HivapParameterFrame->AddFrame(hsplitter1, new TGLayoutHints(kLHintsTop | kLHintsExpandX,0,0,10,10));
	hsplitter1->SetBackgroundColor(TColor::RGB2Pixel(0,0,0));

	CalculateFrame = new TGHorizontalFrame(HivapParameterFrame, 800, 40);
	HivapParameterFrame->AddFrame(CalculateFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	CalculateFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));

	ParameterFrame = new TGVerticalFrame(CalculateFrame, 210, 440);
	CalculateFrame->AddFrame(ParameterFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	ParameterFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));

	CfMinFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(CfMinFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	CfMinText = new TGTextEntry(CfMinFrame, new TGTextBuffer(100), 10000);
	CfMinText->SetText("Cf(min) = ");
	CfMinFrame->AddFrame(CfMinText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	CfMinText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	CfMinText->SetAlignment(kTextCenterX);
	CfMinText->Resize(140, 40);
	CfMinText->SetEnabled(kFALSE);
	CfMinText->SetFrameDrawn(kFALSE);
	CfMinText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	CfMinText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	CfMinNumber = new TGNumberEntry(CfMinFrame, 0, 0, TGNumberFormat::kNESInteger);
	CfMinFrame->AddFrame(CfMinNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	CfMinNumber->GetButtonUp()->ChangeOptions(CfMinNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	CfMinNumber->GetButtonDown()->ChangeOptions(CfMinNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	CfMinNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	CfMinNumber->Resize(100, 40);
	CfMinNumber->SetNumber(0.63);
	CfMinNumber->Associate(this);

	CfMaxFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(CfMaxFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	CfMaxText = new TGTextEntry(CfMaxFrame, new TGTextBuffer(100), 10000);
	CfMaxText->SetText("Cf(max) = ");
	CfMaxFrame->AddFrame(CfMaxText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	CfMaxText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	CfMaxText->SetAlignment(kTextCenterX);
	CfMaxText->Resize(140, 40);
	CfMaxText->SetEnabled(kFALSE);
	CfMaxText->SetFrameDrawn(kFALSE);
	CfMaxText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	CfMaxText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	CfMaxNumber = new TGNumberEntry(CfMaxFrame, 0, 0, TGNumberFormat::kNESInteger);
	CfMaxFrame->AddFrame(CfMaxNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	CfMaxNumber->GetButtonUp()->ChangeOptions(CfMaxNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	CfMaxNumber->GetButtonDown()->ChangeOptions(CfMaxNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	CfMaxNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	CfMaxNumber->Resize(100, 40);
	CfMaxNumber->SetNumber(0.63);
	CfMaxNumber->Associate(this);

	CfDetFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(CfDetFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	CfDetText = new TGTextEntry(CfDetFrame, new TGTextBuffer(100), 10000);
	CfDetText->SetText("Cf(Det) = ");
	CfDetFrame->AddFrame(CfDetText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	CfDetText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	CfDetText->SetAlignment(kTextCenterX);
	CfDetText->Resize(140, 40);
	CfDetText->SetEnabled(kFALSE);
	CfDetText->SetFrameDrawn(kFALSE);
	CfDetText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	CfDetText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	CfDetNumber = new TGNumberEntry(CfDetFrame, 0, 0, TGNumberFormat::kNESInteger);
	CfDetFrame->AddFrame(CfDetNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	CfDetNumber->GetButtonUp()->ChangeOptions(CfDetNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	CfDetNumber->GetButtonDown()->ChangeOptions(CfDetNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	CfDetNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	CfDetNumber->Resize(100, 40);
	CfDetNumber->SetNumber(0.01);
	CfDetNumber->Associate(this);

	Af_AnMinFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(Af_AnMinFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	Af_AnMinText = new TGTextEntry(Af_AnMinFrame, new TGTextBuffer(100), 10000);
	Af_AnMinText->SetText("Af_An(min) = ");
	Af_AnMinFrame->AddFrame(Af_AnMinText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	Af_AnMinText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	Af_AnMinText->SetAlignment(kTextCenterX);
	Af_AnMinText->Resize(140, 40);
	Af_AnMinText->SetEnabled(kFALSE);
	Af_AnMinText->SetFrameDrawn(kFALSE);
	Af_AnMinText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	Af_AnMinText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	Af_AnMinNumber = new TGNumberEntry(Af_AnMinFrame, 0, 0, TGNumberFormat::kNESInteger);
	Af_AnMinFrame->AddFrame(Af_AnMinNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	Af_AnMinNumber->GetButtonUp()->ChangeOptions(Af_AnMinNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	Af_AnMinNumber->GetButtonDown()->ChangeOptions(Af_AnMinNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	Af_AnMinNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	Af_AnMinNumber->Resize(100, 40);
	Af_AnMinNumber->SetNumber(1.0);
	Af_AnMinNumber->Associate(this);

	Af_AnMaxFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(Af_AnMaxFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	Af_AnMaxText = new TGTextEntry(Af_AnMaxFrame, new TGTextBuffer(100), 10000);
	Af_AnMaxText->SetText("Af_An(max) = ");
	Af_AnMaxFrame->AddFrame(Af_AnMaxText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	Af_AnMaxText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	Af_AnMaxText->SetAlignment(kTextCenterX);
	Af_AnMaxText->Resize(140, 40);
	Af_AnMaxText->SetEnabled(kFALSE);
	Af_AnMaxText->SetFrameDrawn(kFALSE);
	Af_AnMaxText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	Af_AnMaxText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	Af_AnMaxNumber = new TGNumberEntry(Af_AnMaxFrame, 0, 0, TGNumberFormat::kNESInteger);
	Af_AnMaxFrame->AddFrame(Af_AnMaxNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	Af_AnMaxNumber->GetButtonUp()->ChangeOptions(Af_AnMaxNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	Af_AnMaxNumber->GetButtonDown()->ChangeOptions(Af_AnMaxNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	Af_AnMaxNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	Af_AnMaxNumber->Resize(100, 40);
	Af_AnMaxNumber->SetNumber(1.0);
	Af_AnMaxNumber->Associate(this);

	Af_AnDetFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(Af_AnDetFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	Af_AnDetText = new TGTextEntry(Af_AnDetFrame, new TGTextBuffer(100), 10000);
	Af_AnDetText->SetText("Af_An(Det) = ");
	Af_AnDetFrame->AddFrame(Af_AnDetText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	Af_AnDetText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	Af_AnDetText->SetAlignment(kTextCenterX);
	Af_AnDetText->Resize(140, 40);
	Af_AnDetText->SetEnabled(kFALSE);
	Af_AnDetText->SetFrameDrawn(kFALSE);
	Af_AnDetText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	Af_AnDetText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	Af_AnDetNumber = new TGNumberEntry(Af_AnDetFrame, 0, 0, TGNumberFormat::kNESInteger);
	Af_AnDetFrame->AddFrame(Af_AnDetNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	Af_AnDetNumber->GetButtonUp()->ChangeOptions(Af_AnDetNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	Af_AnDetNumber->GetButtonDown()->ChangeOptions(Af_AnDetNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	Af_AnDetNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	Af_AnDetNumber->Resize(100, 40);
	Af_AnDetNumber->SetNumber(0.1);
	Af_AnDetNumber->Associate(this);

	FindButtonFrame = new TGHorizontalFrame(ParameterFrame, 240, 40);
	ParameterFrame->AddFrame(FindButtonFrame, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	FindButtonFrame = new TGHorizontalFrame(ParameterFrame, 240, 40);
    ParameterFrame->AddFrame(FindButtonFrame, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
    FindButtonFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
    FindB = new TGTextButton(FindButtonFrame, "Find", FindButton);
    FindButtonFrame->AddFrame(FindB, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 30, 0, 0, 0));
    FindB->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
    FindB->Resize(80, 40);
    FindB->SetTextColor(TColor::RGB2Pixel(255, 255, 255));
    FindB->SetBackgroundColor(TColor::RGB2Pixel(34, 151, 159));
    FindB->Associate(this);


	CanvasFrame = new TGVerticalFrame(CalculateFrame, 1200, 600);
	CalculateFrame->AddFrame(CanvasFrame, new TGLayoutHints(kLHintsTop | kLHintsRight, 0, 0, 0, 0));
	CanvasFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	CfResidualCanvasFrame = new TGHorizontalFrame(CanvasFrame, 600, 600);
	CanvasFrame->AddFrame(CfResidualCanvasFrame, new TGLayoutHints(kLHintsTop | kLHintsRight, 0, 0, 0, 0));
	CfResidualCanvasFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	TGVSplitter *vsplitter1 = new TGVSplitter(CfResidualCanvasFrame, 10, 600);
	CfResidualCanvasFrame->AddFrame(vsplitter1, new TGLayoutHints(kLHintsTop | kLHintsExpandX,0,0,10,10));
	vsplitter1->SetBackgroundColor(TColor::RGB2Pixel(0,0,0));

	ResidualCanvasFrame = new TGVerticalFrame(CfResidualCanvasFrame, 590, 600);
	CfResidualCanvasFrame->AddFrame(ResidualCanvasFrame, new TGLayoutHints(kLHintsTop | kLHintsRight, 0, 0, 0, 0));
	ResidualCanvasFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	ResidualFrameCanvas = new TRootEmbeddedCanvas("Residual", ResidualCanvasFrame, 600, 600);
	ResidualCanvasFrame->AddFrame(ResidualFrameCanvas, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0));
	Int_t Residualwid = ResidualFrameCanvas->GetCanvasWindowId();
	TCanvas *canResidual = new TCanvas("Residual Canvas", 1780, 1200, Residualwid);
	canResidual->ToggleEventStatus();
	canResidual->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "gui", this, "EventInfo(Int_t,Int_t,Int_t,TObject*)");
	ResidualFrameCanvas->AdoptCanvas(canResidual);

	TGVSplitter *vsplitter0 = new TGVSplitter(CfResidualCanvasFrame,10,600);
	CfResidualCanvasFrame->AddFrame(vsplitter0, new TGLayoutHints(kLHintsTop | kLHintsExpandX,0,0,10,10));
	vsplitter0->SetBackgroundColor(TColor::RGB2Pixel(0,0,0));

	CfCanvasFrame = new TGVerticalFrame(CfResidualCanvasFrame, 590, 600);
	CfResidualCanvasFrame->AddFrame(CfCanvasFrame, new TGLayoutHints(kLHintsTop | kLHintsRight, 0, 0, 0, 0));
	CfCanvasFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	CfFrameCanvas = new TRootEmbeddedCanvas("Cf", CfCanvasFrame, 600, 600);
	CfCanvasFrame->AddFrame(CfFrameCanvas, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0));
	Int_t Cfwid = CfFrameCanvas->GetCanvasWindowId();
	TCanvas *Cfcan  = new TCanvas("Cf Canvas", 1780, 1200, Cfwid);
	Cfcan->ToggleEventStatus();
	Cfcan->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "gui", this, "EventInfo(Int_t,Int_t,Int_t,TObject*)");
	CfFrameCanvas->AdoptCanvas(Cfcan);



//	ProgressBarFram = new TGHorizontalFrame(CalculateFrame, 790, 40);
//	CalculateFrame->AddFrame(ProgressBarFram, new TGLayoutHints(kLHintsTop | kLHintsRight, 0, 0, 0, 0));
	ProgressBar = new TGHProgressBar(CanvasFrame, TGProgressBar::kStandard, 1200);
	CanvasFrame->AddFrame(ProgressBar, new TGLayoutHints(kLHintsTop | kLHintsRight, 0, 0, 0, 0));
	ProgressBar->ShowPosition();
	ProgressBar->SetWidth(1200);
//	ProgressBar->SetSize(50);
	ProgressBar->SetBarColor("yellow");

	MapSubwindows();
	Resize();
	CenterOnParent();
	SetWindowName(name);
	MapWindow();
	EvaporationProtonNumber = 5;
	EvaporationNeutronNumber = 11;
}

hivapParameter::~hivapParameter(){}

Bool_t hivapParameter::ProcessMessage(Long_t msg,Long_t parm1, Long_t parm2)
{
	switch (GET_MSG(msg))
	{
		case kC_COMMAND:
			switch (GET_SUBMSG(msg))
			{
				case kCM_BUTTON:
					switch (parm1)
					{
						case FindButton:
						{
							// 检查Ｎ　Ｚ　是否为同一核
							FusionMinNNumber->GetNumberEntry()->SetTextColor(TColor::RGB2Pixel(0, 0, 0));
							if(Int_t(FusionMinZNumber->GetNumber())+Int_t(FusionMinNNumber->GetNumber()) != Int_t(FusionMinANumber->GetNumber()))
							{
								FusionMinNNumber->SetNumber(FusionMinANumber->GetNumber()-FusionMinZNumber->GetNumber());
								FusionMinNNumber->GetNumberEntry()->SetTextColor(TColor::RGB2Pixel(255, 0, 0));
							}

							FusionMaxNNumber->GetNumberEntry()->SetTextColor(TColor::RGB2Pixel(0, 0, 0));
							if(Int_t(FusionMaxZNumber->GetNumber())+Int_t(FusionMaxNNumber->GetNumber()) != Int_t(FusionMaxANumber->GetNumber()))
							{
								FusionMaxNNumber->SetNumber(FusionMaxANumber->GetNumber()-FusionMaxZNumber->GetNumber());
								FusionMaxNNumber->GetNumberEntry()->SetTextColor(TColor::RGB2Pixel(255, 0, 0));
							}
							
							CrossSectionExpVe.clear();
							CrossSectionExp CrossSectionExpTmp;
							ifstream FinCrossSectionExp;
							FinCrossSectionExp.open("./data/cross-section.txt");
							if(FusionMinZNumber->GetNumber() <= FusionMaxZNumber->GetNumber() 
							&& FusionMinANumber->GetNumber() <= FusionMaxANumber->GetNumber())
							{
								if(FinCrossSectionExp.is_open())
								{
									std::string strtmp;
									getline(FinCrossSectionExp, strtmp);
									while(FinCrossSectionExp >> CrossSectionExpTmp.ZFER >> CrossSectionExpTmp.AFER 
														 >> CrossSectionExpTmp.Channel
														 >> CrossSectionExpTmp.Zp >> CrossSectionExpTmp.Ap
														 >> CrossSectionExpTmp.Zt >> CrossSectionExpTmp.At
														 >> CrossSectionExpTmp.BeamEnergy 
														 >> CrossSectionExpTmp.CrossSectionub >> CrossSectionExpTmp.ErrCrossSectionub
														 >> CrossSectionExpTmp.Facility
														 >> CrossSectionExpTmp.Cf >> CrossSectionExpTmp.Af_An)
									{
										if(
							(CrossSectionExpTmp.Zp + CrossSectionExpTmp.Zt) >= FusionMinZNumber->GetNumber() && 
							(CrossSectionExpTmp.Zp + CrossSectionExpTmp.Zt) <= FusionMaxZNumber->GetNumber() &&
						  	(CrossSectionExpTmp.Ap + CrossSectionExpTmp.At)	>= FusionMinANumber->GetNumber() &&
							(CrossSectionExpTmp.Ap + CrossSectionExpTmp.At) <= FusionMaxANumber->GetNumber() )
										{
											CrossSectionExpTmp.CrossSectionubCal = 0.0;
											CrossSectionExpVe.push_back(CrossSectionExpTmp);
										}
//									std::cout << CrossSectionExpTmp.CrossSectionub << std::endl;
									}
//								std::cout << CrossSectionExpVe.size() << std::endl; 
								}
								else
									std::cout << "Cannot open ./data/cross-section.txt " << std::endl;
								FinCrossSectionExp.close();
							}
							else
								std::cout << "The information of the fusion is erroe! " << endl;
							Double_t ProcessTmp = 0.0;
							for(Int_t i = 0; i < Int_t(CrossSectionExpVe.size()); i++)
							{
								if(Af_AnMinNumber->GetNumber() <= Af_AnMaxNumber->GetNumber()
								&& CfMinNumber->GetNumber() <= CfMaxNumber->GetNumber())
								{
									Double_t CrossSectionResidual = 1.0E5;
									for(Double_t Af_AnTmp = Double_t(Af_AnMinNumber->GetNumber()); Af_AnTmp <= Double_t(Af_AnMaxNumber->GetNumber()); Af_AnTmp += Double_t(Af_AnDetNumber->GetNumber()))
									{
										for(Double_t CfTmp = Double_t(CfMinNumber->GetNumber()); CfTmp <= Double_t(CfMaxNumber->GetNumber()); CfTmp += Double_t(CfDetNumber->GetNumber()))
										{
											MakeHivapInputfile(CrossSectionExpVe.at(i).Zp, CrossSectionExpVe.at(i).Ap, CrossSectionExpVe.at(i).Zt, CrossSectionExpVe.at(i).At, CrossSectionExpVe.at(i).BeamEnergy, Af_AnTmp, CfTmp);
											system("./Hivap/hivapn>>log.txt");
											Double_t CrossSectionubCalTmp = 1.0E3 * ReadCalCulatedCrossSection(CrossSectionExpVe.at(i).ZFER, CrossSectionExpVe.at(i).AFER, CrossSectionExpVe.at(i).Zp, CrossSectionExpVe.at(i).Ap, CrossSectionExpVe.at(i).Zt, CrossSectionExpVe.at(i).At);
											if(abs(CrossSectionubCalTmp - CrossSectionExpVe.at(i).CrossSectionub) < CrossSectionResidual)
											{
												CrossSectionExpVe.at(i).Cf = CfTmp;
												CrossSectionExpVe.at(i).Af_An = Af_AnTmp;
												CrossSectionExpVe.at(i).CrossSectionubCal = CrossSectionubCalTmp;
												CrossSectionResidual = abs(CrossSectionubCalTmp - CrossSectionExpVe.at(i).CrossSectionub);
											}
											ProcessTmp += 1.0;
											ProgressBar->SetPosition(100.0*ProcessTmp/(Double_t(CrossSectionExpVe.size())*(1.0 + Double_t(CfMaxNumber->GetNumber() - CfMinNumber->GetNumber())/Double_t(CfDetNumber->GetNumber()))* (1.0 + Double_t(Af_AnMaxNumber->GetNumber() - Af_AnMinNumber->GetNumber())/Double_t(CfDetNumber->GetNumber()))));
										}
									}
								}
								else
									std::cout << "The information of the Cf or af/an is error! " << std::endl;
							}
							for(auto it = CrossSectionExpVe.begin(); it != CrossSectionExpVe.end(); it++)
							{
								if(it->CrossSectionubCal == 0)
										it = CrossSectionExpVe.erase(it);
							}
							Draw();
							
							break;
						}
						default:
							break;
					}
				default:
					break;
			}
		default:
			break;
	}
	return kTRUE;
}

void hivapParameter::MakeHivapInputfile(Int_t ZpIn, Int_t ApIn, Int_t ZtIn, Int_t AtIn, Double_t BeamEnergy, Double_t Af_AnIn, Double_t CfIn)
{
    std::ofstream fileout("./Hivap/hivapein.dat");
    std::ifstream filein("./Hivap/hivapeintmp.dat");
    std::string stmp;
    double dtmp;
    int itmp;
    if(filein.is_open())
    {   
        int n = 0;  
        while(getline(filein, stmp))
        {
            fileout << stmp;
            fileout << std::endl;
            n++;
            if(n==2)
            {
                filein >> stmp >> itmp;
                fileout << "  " << stmp << "  " << ApIn <<"  ";
                filein >> stmp >> itmp;
                fileout << stmp << "  " << ZpIn <<"  ";
                filein >> stmp >> itmp;
                fileout << stmp << "  " << AtIn <<"  ";
                filein >> stmp >> itmp;
                fileout << stmp << "  " << ZtIn <<"  ";
                getline(filein, stmp);
                fileout << std::endl;
                n++;
            }

            if(n==8)
            {
                filein >> stmp >> itmp;
                fileout << "  " << stmp << "  " << EvaporationNeutronNumber <<"  ";
                filein >> stmp >> itmp;
                fileout << stmp << "  " << EvaporationProtonNumber <<"  ";
                getline(filein, stmp);
                fileout << std::endl;
                n++;
            }
            if(n==22)
            {
                filein >> stmp >> dtmp;
                fileout << "  " << stmp << "  " << dtmp <<"  ";
                filein >> stmp >> dtmp;
                fileout << stmp << "  " << Af_AnIn <<"  ";
                filein >> stmp >> dtmp;
                fileout << stmp << "  " << CfIn  <<"  ";
                getline(filein, stmp);
                fileout << stmp << std::endl;
                n++;
            }
            if(n==31)
            {
                filein >> stmp >> dtmp;
                fileout << "  " << stmp << "  " << BeamEnergy;
                filein >> stmp >> dtmp;
                fileout << "  " << stmp << "  " << 0;
                getline(filein, stmp);
                fileout << stmp << std::endl;
                n++;
            }
        }
    }
	else
		std::cout<< "Cannot open ./Hivap/hivapeintmp.dat" << std::endl;
    fileout.close();
    filein.close();	
}

Double_t hivapParameter::ReadCalCulatedCrossSection(Int_t ZpIn, Int_t ApIn, Int_t ZtIn, Int_t AtIn, Int_t ZFERIn, Int_t AFERIn)
{
	Double_t CalculatedCrossSectionTmp = 0.0;
	std::ifstream HIVAP_file("./Hivap/hivaperg.dat");
	std::string stmp;
	Double_t dtmp;
	if(HIVAP_file.is_open())
	{
		HIVAP_file>>stmp;
		HIVAP_file>>dtmp;
		HIVAP_file>>stmp;
//		cout << "Q  =  " << dtmp << " " << stmp << endl;
		getline(HIVAP_file, stmp);
		getline(HIVAP_file, stmp);

		for(int i = 0; i < 2 * EvaporationProtonNumber; i++)
		{
    		getline(HIVAP_file, stmp);
		}
		getline(HIVAP_file, stmp);
		HIVAP_file>>stmp;
		HIVAP_file>>dtmp;
//		cout << "Cf = " << dtmp << endl;
		getline(HIVAP_file, stmp);
		for(int i = 0; i < 3 * EvaporationProtonNumber; i++)
		{
    		getline(HIVAP_file, stmp);
		}
		getline(HIVAP_file, stmp);
		getline(HIVAP_file, stmp);
		getline(HIVAP_file, stmp);
		getline(HIVAP_file, stmp);
		getline(HIVAP_file, stmp);
		while(getline(HIVAP_file, stmp))
		{
			//std::cout<<stmp <<endl;
    		string stmptmp;
    		if(stmp.size()>5)
    		{
        		stmptmp = stmp.substr(1, 5);
        		if(stmptmp=="HIVAP")
        		{
            		getline(HIVAP_file, stmp);
            		getline(HIVAP_file, stmp);
            		getline(HIVAP_file, stmp);
            		getline(HIVAP_file, stmp);
            		getline(HIVAP_file, stmp);
            		getline(HIVAP_file, stmp);
            		while(1)
            		{
                		getline(HIVAP_file, stmp);
						 //std::cout<<stmp <<endl;
                		if(stmp.size()!=0)
                		{
                    		HIVAP_file.seekg(-stmp.size(), HIVAP_file.cur);
                    		HIVAP_file >> dtmp >> dtmp >> dtmp >> dtmp >> dtmp >> dtmp >> dtmp >> dtmp;
                        	getline(HIVAP_file, stmp);
						}
             			else
                    		break;
          			}
     			}
			}
       		if(stmp.size()>17)
			{
    			stmptmp = stmp.substr(5, 12);
    			if(stmptmp=="Querschnitte")
    			{
        			getline(HIVAP_file, stmp);
//					std::cout<<stmp <<endl;
        			for(int nz = 0; nz <EvaporationProtonNumber; nz++)
        			{
            			HIVAP_file >> stmp;
        				getline(HIVAP_file, stmp);
            			getline(HIVAP_file, stmp);
            			while(1)
            			{
                			if(stmp.size()!=0)
                			{
                    			HIVAP_file.seekg(-stmp.size(), HIVAP_file.cur);
                    			HIVAP_file >> dtmp;
                    			for(int i = 0; i < EvaporationNeutronNumber; i++)
                    			{
                        			HIVAP_file >> CalculatedCrossSectionTmp;
									if(ZFERIn == (ZpIn + ZtIn - nz) && AFERIn == (ApIn + AtIn - nz - (EvaporationNeutronNumber - i) + 1))
											return CalculatedCrossSectionTmp;
                    			}
                    			getline(HIVAP_file, stmp);
                    			getline(HIVAP_file, stmp);
                			}
                			else
                    			break;
            			}
        			}
				}
  			}
        }
	}
	else
		std::cout << "Cannot open ./Hivap/hivaperg.dat" << std::endl;
	HIVAP_file.close();
	return CalculatedCrossSectionTmp;
}

void hivapParameter::Draw()
{
	Int_t nZDraw = 120;
	TGraphErrors *gCrossSectionResidual[nZDraw];
	Int_t* gCrossSectionResidual_np = new Int_t[nZDraw];
	TGraphErrors *gCf[nZDraw];
	Int_t* gCf_np = new Int_t[nZDraw];
	for(int i=0; i<nZDraw; i++)
	{
			gCrossSectionResidual[i] = new TGraphErrors;
			gCrossSectionResidual_np[i] = 0;
			gCf[i] = new TGraphErrors;
			gCf_np[i] = 0;
	}
	sort(CrossSectionExpVe.begin(), CrossSectionExpVe.end(), SortAFER);
	for(int i = 0; i < Int_t(CrossSectionExpVe.size()); i++)
	{
		Int_t ZTmp = CrossSectionExpVe.at(i).ZFER;
		Int_t ATmp = CrossSectionExpVe.at(i).AFER;
		Double_t CrossSectionExpTmp = CrossSectionExpVe.at(i).CrossSectionub;
		Double_t CrossSectionCalTmp = CrossSectionExpVe.at(i).CrossSectionubCal;
		if(CrossSectionCalTmp != 0 || CrossSectionExpTmp != 0)
			gCrossSectionResidual[ZTmp]->SetPoint(gCrossSectionResidual_np[ZTmp], ATmp, log10(CrossSectionCalTmp/CrossSectionExpTmp));
		else
			std::cout << CrossSectionExpVe.at(i).ZFER <<"  "<< CrossSectionExpVe.at(i).AFER <<"  "<<CrossSectionExpVe.at(i).Zp <<"  " << CrossSectionExpVe.at(i).Ap <<"  "<<CrossSectionCalTmp <<"   "<<CrossSectionExpTmp <<"    "<< (CrossSectionCalTmp/CrossSectionExpTmp)<< "  " << log10(CrossSectionCalTmp/CrossSectionExpTmp) << std::endl;
		gCrossSectionResidual_np[ZTmp]++;
	}
	sort(CrossSectionExpVe.begin(), CrossSectionExpVe.end(), SortAFusion);
	for(int i = 0; i < Int_t(CrossSectionExpVe.size()); i++)
	{
		Int_t ZTmp = CrossSectionExpVe.at(i).Zp + CrossSectionExpVe.at(i).Zt;
		Int_t ATmp = CrossSectionExpVe.at(i).Ap + CrossSectionExpVe.at(i).At;
		gCf[ZTmp]->SetPoint(gCf_np[ZTmp], ATmp, CrossSectionExpVe.at(i).Cf);
		gCf_np[ZTmp]++;
	}
	Int_t ngraph = 0;

    for(int i=0; i < nZDraw; i++)
    {
        	if(gCrossSectionResidual[i]->GetN() > 0)
        	{
	
            	if(ngraph < 11)
            	{
                	gCrossSectionResidual[i]->SetMarkerStyle(20 + ngraph);
            	}
            	else if(ngraph <= 22)
            	{
                	gCrossSectionResidual[i]->SetMarkerStyle(9 + ngraph);
            	}
            	else if(ngraph <= 33)
            	{
                	gCrossSectionResidual[i]->SetMarkerStyle(ngraph-2);
            	}
            	gCrossSectionResidual[i]->SetMarkerSize(1.0);
            	if(ngraph < 11)
            	{
					if(ngraph+3==5)
					{
						gCrossSectionResidual[i]->SetMarkerColor(96);
						gCrossSectionResidual[i]->SetLineColor(96);
					}
                	else if(ngraph+3 == 10) 
					{
						gCrossSectionResidual[i]->SetMarkerColor(50);
						gCrossSectionResidual[i]->SetLineColor(50);
					}
                	else 
					{
						gCrossSectionResidual[i]->SetMarkerColor(ngraph+3);
						gCrossSectionResidual[i]->SetLineColor(ngraph+3);
					}
            	}
            	else
            	{
                	gCrossSectionResidual[i]->SetMarkerColor(3*ngraph+3);
                	gCrossSectionResidual[i]->SetLineColor(3*ngraph+3);
            	}
            	gCrossSectionResidual[i]->SetLineStyle(7);
            	gCrossSectionResidual[i]->SetLineWidth(1);
				gCrossSectionResidual[i]->SetMarkerSize(1.5);
            	ngraph++;
        	}
	}
	ngraph = 0;	        
    for(int i=0; i < nZDraw; i++)
    {
        	if(gCf[i]->GetN() > 0)
        	{
	
            	if(ngraph < 11)
            	{
                	gCf[i]->SetMarkerStyle(20 + ngraph);
            	}
            	else if(ngraph <= 22)
            	{
                	gCf[i]->SetMarkerStyle(9 + ngraph);
            	}
            	else if(ngraph <= 33)
            	{
                	gCf[i]->SetMarkerStyle(ngraph-2);
            	}
				gCf[i]->SetMarkerSize(1.0);
            	if(ngraph < 11)
            	{
					if(ngraph+3==5)
					{
						gCf[i]->SetMarkerColor(96);
						gCf[i]->SetLineColor(96);
					}
                	else if(ngraph+3 == 10) 
					{
						gCf[i]->SetMarkerColor(50);
						gCf[i]->SetLineColor(50);
					}
                	else 
					{
						gCf[i]->SetMarkerColor(ngraph+3);
						gCf[i]->SetLineColor(ngraph+3);
					}
            	}
            	else
            	{
					gCf[i]->SetMarkerColor(3*ngraph+3);
					gCf[i]->SetLineColor(3*ngraph+3);
            	}
            	gCf[i]->SetLineStyle(1);
            	gCf[i]->SetLineWidth(2);
				gCf[i]->SetMarkerSize(1.5);
            	ngraph++;
        	}
	}
	TMultiGraph *mgCrossSectionResidual = new TMultiGraph();		
	TLegend *legCrossSectionResidual = new TLegend(0.84, 0.1, 0.999, 0.9);
    for(int i=0; i < nZDraw; i++)
    {
        	if(gCrossSectionResidual[i]->GetN() > 0)
        	{
				mgCrossSectionResidual->Add(gCrossSectionResidual[i], "P");
				nuclear_data *nuclear_dataTmp = new nuclear_data(i, i, 2*i);
				TString nameTmp = nuclear_dataTmp->getname();
            	legCrossSectionResidual->AddEntry(gCrossSectionResidual[i], nameTmp);
			}
	}
	TMultiGraph *mgCf = new TMultiGraph();		
	TLegend *legCf = new TLegend(0.84, 0.5, 0.999, 0.9);
    for(int i=0; i < nZDraw; i++)
    {
        	if(gCf[i]->GetN() > 0)
        	{
				mgCf->Add(gCf[i], "P");
				nuclear_data *nuclear_dataTmp = new nuclear_data(i, i, 2*i);
				TString nameTmp = nuclear_dataTmp->getname();
            	legCf->AddEntry(gCf[i], nameTmp);
			}
	}
	mgCf->SetTitle("; A; Cf");
	mgCf->GetYaxis()->CenterTitle("1");
	mgCf->GetXaxis()->CenterTitle("1");
	mgCf->GetXaxis()->SetTitleOffset(1.4);
	mgCf->GetYaxis()->SetTitleOffset(1.4);
//	mgCf->GetYaxis()->SetRangeUser(0.45, 0.75);
//	mgCf->GetXaxis()->SetRangeUser(183, 203);

//	TLatex *texta = new TLatex(DrawVBassNumber->GetNumber()-5, 18*DrawYminNumber->GetNumber(), "B_{Bass}");
	TCanvas *CfDrawCanvastmp = CfFrameCanvas->GetCanvas();
//	std::cout << "\033[31m bg5 \033[0m" << endl;
	CfDrawCanvastmp->ToggleEventStatus();
	CfDrawCanvastmp->cd();
	mgCf->Draw("A");
	legCf->SetTextFont(22);
	legCf->SetTextSize(0.04);
	legCf->SetMargin(0.6);
	legCf->Draw();
	CfDrawCanvastmp->Modified();
	CfDrawCanvastmp->Update();

	mgCrossSectionResidual->SetTitle("; #sigma(Cal.)/#sigma(Exp.); A");
	mgCrossSectionResidual->GetYaxis()->CenterTitle("1");
	mgCrossSectionResidual->GetXaxis()->CenterTitle("1");
	mgCrossSectionResidual->GetXaxis()->SetTitleOffset(1.4);
	mgCrossSectionResidual->GetYaxis()->SetTitleOffset(1.4);
//	mgCrossSectionResidual->GetXaxis()->SetRangeUser(183, 203);
//	mgCrossSectionResidual->GetYaxis()->SetRangeUser(-15.0, 4.0);

	TCanvas *ResidualDrawCanvastmp = ResidualFrameCanvas->GetCanvas();
	ResidualDrawCanvastmp->ToggleEventStatus();
	ResidualDrawCanvastmp->cd();
	mgCrossSectionResidual->Draw("A");
	legCrossSectionResidual->SetTextFont(22);
	legCrossSectionResidual->SetTextSize(0.04);
	legCrossSectionResidual->SetMargin(0.6);
	legCrossSectionResidual->Draw();
//	DrawCanvastmp->SetLogy(1);
	ResidualDrawCanvastmp->Modified();
	ResidualDrawCanvastmp->Update();
}


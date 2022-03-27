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

#include "hivap.h"
#include "iostream"

hivap::hivap(const TGWindow * p, const TGWindow * main, char *name)
{
	SetCleanup(kDeepCleanup);
	SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	ngraph_Draw = 0;

	HivapFrame = new TGVerticalFrame(this, 800, 1500);
	AddFrame(HivapFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 10, 10, 5, 5));
	HivapFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	TGHSplitter *hsplitter0 = new TGHSplitter(HivapFrame,200,2);
	HivapFrame->AddFrame(hsplitter0, new TGLayoutHints(kLHintsTop | kLHintsExpandX,0,0,10,10));

	ProjectileFrame = new TGHorizontalFrame(HivapFrame, 800, 40);
	HivapFrame->AddFrame(ProjectileFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	ProjectileFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));

	ProjectileText = new TGTextEntry(ProjectileFrame, new TGTextBuffer(100), 10000);
	ProjectileText->SetText("Projectile : ");
	ProjectileFrame->AddFrame(ProjectileText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	ProjectileText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	ProjectileText->Resize(150, 40);
	ProjectileText->SetEnabled(kFALSE);
	ProjectileText->SetFrameDrawn(kFALSE);
	ProjectileText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	ProjectileText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	ProjectileZText = new TGTextEntry(ProjectileFrame, new TGTextBuffer(100), 10000);
	ProjectileZText->SetText("Z = ");
	ProjectileFrame->AddFrame(ProjectileZText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	ProjectileZText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	ProjectileZText->SetAlignment(kTextCenterX);
	ProjectileZText->Resize(200, 40);
	ProjectileZText->SetEnabled(kFALSE);
	ProjectileZText->SetFrameDrawn(kFALSE);
	ProjectileZText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	ProjectileZText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	ProjectileZNumber = new TGNumberEntry(ProjectileFrame, 0, 0, TGNumberFormat::kNESInteger);
	ProjectileFrame->AddFrame(ProjectileZNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	ProjectileZNumber->GetButtonUp()->ChangeOptions(ProjectileZNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	ProjectileZNumber->GetButtonDown()->ChangeOptions(ProjectileZNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	ProjectileZNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	ProjectileZNumber->Resize(100, 40);
	ProjectileZNumber->SetNumber(20);
	ProjectileZNumber->Associate(this);

	ProjectileAText = new TGTextEntry(ProjectileFrame, new TGTextBuffer(100), 10000);
	ProjectileAText->SetText("A = ");
	ProjectileFrame->AddFrame(ProjectileAText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	ProjectileAText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	ProjectileAText->SetAlignment(kTextCenterX);
	ProjectileAText->Resize(200, 40);
	ProjectileAText->SetEnabled(kFALSE);
	ProjectileAText->SetFrameDrawn(kFALSE);
	ProjectileAText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	ProjectileAText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	ProjectileANumber = new TGNumberEntry(ProjectileFrame, 0, 0, TGNumberFormat::kNESInteger);
	ProjectileFrame->AddFrame(ProjectileANumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	ProjectileANumber->GetButtonUp()->ChangeOptions(ProjectileANumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	ProjectileANumber->GetButtonDown()->ChangeOptions(ProjectileANumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	ProjectileANumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	ProjectileANumber->Resize(100, 40);
	ProjectileANumber->SetNumber(48);
	ProjectileANumber->Associate(this);

	ProjectileNText = new TGTextEntry(ProjectileFrame, new TGTextBuffer(100), 10000);
	ProjectileNText->SetText("N = ");
	ProjectileFrame->AddFrame(ProjectileNText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	ProjectileNText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	ProjectileNText->SetAlignment(kTextCenterX);
	ProjectileNText->Resize(190, 40);
	ProjectileNText->SetEnabled(kFALSE);
	ProjectileNText->SetFrameDrawn(kFALSE);
	ProjectileNText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	ProjectileNText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	ProjectileNNumber = new TGNumberEntry(ProjectileFrame, 0, 0, TGNumberFormat::kNESInteger);
	ProjectileFrame->AddFrame(ProjectileNNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	ProjectileNNumber->GetButtonUp()->ChangeOptions(ProjectileNNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	ProjectileNNumber->GetButtonDown()->ChangeOptions(ProjectileNNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	ProjectileNNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	ProjectileNNumber->Resize(100, 40);
	ProjectileNNumber->SetNumber(28);
	ProjectileNNumber->Associate(this);
	
	TargetFrame = new TGHorizontalFrame(HivapFrame, 800, 40);
	HivapFrame->AddFrame(TargetFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	TargetFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));

	TargetText = new TGTextEntry(TargetFrame, new TGTextBuffer(100), 10000);
	TargetText->SetText("Target : ");
	TargetFrame->AddFrame(TargetText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	TargetText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	TargetText->Resize(150, 40);
	TargetText->SetEnabled(kFALSE);
	TargetText->SetFrameDrawn(kFALSE);
	TargetText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	TargetText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	TargetZText = new TGTextEntry(TargetFrame, new TGTextBuffer(100), 10000);
	TargetZText->SetText("Z = ");
	TargetFrame->AddFrame(TargetZText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	TargetZText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	TargetZText->SetAlignment(kTextCenterX);
	TargetZText->Resize(200, 40);
	TargetZText->SetEnabled(kFALSE);
	TargetZText->SetFrameDrawn(kFALSE);
	TargetZText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	TargetZText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	TargetZNumber = new TGNumberEntry(TargetFrame, 0, 0, TGNumberFormat::kNESInteger);
	TargetFrame->AddFrame(TargetZNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	TargetZNumber->GetButtonUp()->ChangeOptions(TargetZNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	TargetZNumber->GetButtonDown()->ChangeOptions(TargetZNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	TargetZNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	TargetZNumber->Resize(100, 40);
	TargetZNumber->SetNumber(82);
	TargetZNumber->Associate(this);

	TargetAText = new TGTextEntry(TargetFrame, new TGTextBuffer(100), 10000);
	TargetAText->SetText("A = ");
	TargetFrame->AddFrame(TargetAText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	TargetAText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	TargetAText->SetAlignment(kTextCenterX);
	TargetAText->Resize(200, 40);
	TargetAText->SetEnabled(kFALSE);
	TargetAText->SetFrameDrawn(kFALSE);
	TargetAText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	TargetAText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	TargetANumber = new TGNumberEntry(TargetFrame, 0, 0, TGNumberFormat::kNESInteger);
	TargetFrame->AddFrame(TargetANumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	TargetANumber->GetButtonUp()->ChangeOptions(TargetANumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	TargetANumber->GetButtonDown()->ChangeOptions(TargetANumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	TargetANumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	TargetANumber->Resize(100, 40);
	TargetANumber->SetNumber(208);
	TargetANumber->Associate(this);

	TargetNText = new TGTextEntry(TargetFrame, new TGTextBuffer(100), 10000);
	TargetNText->SetText("N = ");
	TargetFrame->AddFrame(TargetNText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	TargetNText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	TargetNText->SetAlignment(kTextCenterX);
	TargetNText->Resize(190, 40);
	TargetNText->SetEnabled(kFALSE);
	TargetNText->SetFrameDrawn(kFALSE);
	TargetNText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	TargetNText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	TargetNNumber = new TGNumberEntry(TargetFrame, 0, 0, TGNumberFormat::kNESInteger);
	TargetFrame->AddFrame(TargetNNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	TargetNNumber->GetButtonUp()->ChangeOptions(TargetNNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	TargetNNumber->GetButtonDown()->ChangeOptions(TargetNNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	TargetNNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	TargetNNumber->Resize(100, 40);
	TargetNNumber->SetNumber(126);
	TargetNNumber->Associate(this);

	TGHSplitter *hsplitter1 = new TGHSplitter(HivapFrame,800,2);
	HivapFrame->AddFrame(hsplitter1, new TGLayoutHints(kLHintsTop | kLHintsExpandX,0,0,10,10));
	hsplitter1->SetBackgroundColor(TColor::RGB2Pixel(0,0,0));

	CalculateFrame = new TGHorizontalFrame(HivapFrame, 800, 40);
	HivapFrame->AddFrame(CalculateFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	CalculateFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));

	ParameterFrame = new TGVerticalFrame(CalculateFrame, 210, 440);
	CalculateFrame->AddFrame(ParameterFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	ParameterFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));

	EcmMinFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(EcmMinFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	EcmMinText = new TGTextEntry(EcmMinFrame, new TGTextBuffer(100), 10000);
	EcmMinText->SetText("Ecm(min) = ");
	EcmMinFrame->AddFrame(EcmMinText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	EcmMinText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	EcmMinText->SetAlignment(kTextCenterX);
	EcmMinText->Resize(140, 40);
	EcmMinText->SetEnabled(kFALSE);
	EcmMinText->SetFrameDrawn(kFALSE);
	EcmMinText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	EcmMinText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	EcmMinNumber = new TGNumberEntry(EcmMinFrame, 0, 0, TGNumberFormat::kNESInteger);
	EcmMinFrame->AddFrame(EcmMinNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	EcmMinNumber->GetButtonUp()->ChangeOptions(EcmMinNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	EcmMinNumber->GetButtonDown()->ChangeOptions(EcmMinNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	EcmMinNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	EcmMinNumber->Resize(100, 40);
	EcmMinNumber->SetNumber(10);
	EcmMinNumber->Associate(this);

	EcmMaxFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(EcmMaxFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	EcmMaxText = new TGTextEntry(EcmMaxFrame, new TGTextBuffer(100), 10000);
	EcmMaxText->SetText("Ecm(max) = ");
	EcmMaxFrame->AddFrame(EcmMaxText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	EcmMaxText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	EcmMaxText->SetAlignment(kTextCenterX);
	EcmMaxText->Resize(140, 40);
	EcmMaxText->SetEnabled(kFALSE);
	EcmMaxText->SetFrameDrawn(kFALSE);
	EcmMaxText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	EcmMaxText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	EcmMaxNumber = new TGNumberEntry(EcmMaxFrame, 0, 0, TGNumberFormat::kNESInteger);
	EcmMaxFrame->AddFrame(EcmMaxNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	EcmMaxNumber->GetButtonUp()->ChangeOptions(EcmMaxNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	EcmMaxNumber->GetButtonDown()->ChangeOptions(EcmMaxNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	EcmMaxNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	EcmMaxNumber->Resize(100, 40);
	EcmMaxNumber->SetNumber(80);
	EcmMaxNumber->Associate(this);

	EcmDetEFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(EcmDetEFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	EcmDetEText = new TGTextEntry(EcmDetEFrame, new TGTextBuffer(100), 10000);
	EcmDetEText->SetText("Ecm(Det) = ");
	EcmDetEFrame->AddFrame(EcmDetEText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	EcmDetEText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	EcmDetEText->SetAlignment(kTextCenterX);
	EcmDetEText->Resize(140, 40);
	EcmDetEText->SetEnabled(kFALSE);
	EcmDetEText->SetFrameDrawn(kFALSE);
	EcmDetEText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	EcmDetEText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	EcmDetENumber = new TGNumberEntry(EcmDetEFrame, 0, 0, TGNumberFormat::kNESInteger);
	EcmDetEFrame->AddFrame(EcmDetENumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	EcmDetENumber->GetButtonUp()->ChangeOptions(EcmDetENumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	EcmDetENumber->GetButtonDown()->ChangeOptions(EcmDetENumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	EcmDetENumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	EcmDetENumber->Resize(100, 40);
	EcmDetENumber->SetNumber(2);
	EcmDetENumber->Associate(this);

	CfFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(CfFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	CfText = new TGTextEntry(CfFrame, new TGTextBuffer(100), 10000);
	CfText->SetText("Cf = ");
	CfFrame->AddFrame(CfText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	CfText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	CfText->SetAlignment(kTextCenterX);
	CfText->Resize(140, 40);
	CfText->SetEnabled(kFALSE);
	CfText->SetFrameDrawn(kFALSE);
	CfText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	CfText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	CfNumber = new TGNumberEntry(CfFrame, 0, 0, TGNumberFormat::kNESInteger);
	CfFrame->AddFrame(CfNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	CfNumber->GetButtonUp()->ChangeOptions(CfNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	CfNumber->GetButtonDown()->ChangeOptions(CfNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	CfNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	CfNumber->Resize(100, 40);
	CfNumber->SetNumber(0.65);
	CfNumber->Associate(this);

	Af_AnFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(Af_AnFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	Af_AnText = new TGTextEntry(Af_AnFrame, new TGTextBuffer(100), 10000);
	Af_AnText->SetText("af/an = ");
	Af_AnFrame->AddFrame(Af_AnText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	Af_AnText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	Af_AnText->SetAlignment(kTextCenterX);
	Af_AnText->Resize(140, 40);
	Af_AnText->SetEnabled(kFALSE);
	Af_AnText->SetFrameDrawn(kFALSE);
	Af_AnText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	Af_AnText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	Af_AnNumber = new TGNumberEntry(Af_AnFrame, 0, 0, TGNumberFormat::kNESInteger);
	Af_AnFrame->AddFrame(Af_AnNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	Af_AnNumber->GetButtonUp()->ChangeOptions(Af_AnNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	Af_AnNumber->GetButtonDown()->ChangeOptions(Af_AnNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	Af_AnNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	Af_AnNumber->Resize(100, 40);
	Af_AnNumber->SetNumber(1.00);

	EvaporationProtonFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(EvaporationProtonFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	EvaporationProtonText = new TGTextEntry(EvaporationProtonFrame, new TGTextBuffer(100), 10000);
	EvaporationProtonText->SetText("Eva(P) = ");
	EvaporationProtonFrame->AddFrame(EvaporationProtonText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	EvaporationProtonText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	EvaporationProtonText->SetAlignment(kTextCenterX);
	EvaporationProtonText->Resize(140, 40);
	EvaporationProtonText->SetEnabled(kFALSE);
	EvaporationProtonText->SetFrameDrawn(kFALSE);
	EvaporationProtonText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	EvaporationProtonText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	EvaporationProtonNumber = new TGNumberEntry(EvaporationProtonFrame, 0, 0, TGNumberFormat::kNESInteger);
	EvaporationProtonFrame->AddFrame(EvaporationProtonNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	EvaporationProtonNumber->GetButtonUp()->ChangeOptions(EvaporationProtonNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	EvaporationProtonNumber->GetButtonDown()->ChangeOptions(EvaporationProtonNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	EvaporationProtonNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	EvaporationProtonNumber->Resize(100, 40);
	EvaporationProtonNumber->SetNumber(5);
	EvaporationProtonNumber->Associate(this);

	EvaporationNeutronFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(EvaporationNeutronFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	EvaporationNeutronText = new TGTextEntry(EvaporationNeutronFrame, new TGTextBuffer(100), 10000);
	EvaporationNeutronText->SetText("Eva(N) = ");
	EvaporationNeutronFrame->AddFrame(EvaporationNeutronText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	EvaporationNeutronText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	EvaporationNeutronText->SetAlignment(kTextCenterX);
	EvaporationNeutronText->Resize(140, 40);
	EvaporationNeutronText->SetEnabled(kFALSE);
	EvaporationNeutronText->SetFrameDrawn(kFALSE);
	EvaporationNeutronText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	EvaporationNeutronText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	EvaporationNeutronNumber = new TGNumberEntry(EvaporationNeutronFrame, 0, 0, TGNumberFormat::kNESInteger);
	EvaporationNeutronFrame->AddFrame(EvaporationNeutronNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	EvaporationNeutronNumber->GetButtonUp()->ChangeOptions(EvaporationNeutronNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	EvaporationNeutronNumber->GetButtonDown()->ChangeOptions(EvaporationNeutronNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	EvaporationNeutronNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	EvaporationNeutronNumber->Resize(100, 40);
	EvaporationNeutronNumber->SetNumber(9);
	EvaporationNeutronNumber->Associate(this);

	CalculateButtonFrame = new TGHorizontalFrame(ParameterFrame, 240, 40);
	ParameterFrame->AddFrame(CalculateButtonFrame, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	CalculateButtonFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	CalculateB = new TGTextButton(CalculateButtonFrame, "Calculate", CalculateButton);
    CalculateButtonFrame->AddFrame(CalculateB, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 30, 0, 0, 0));
    CalculateB->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
    CalculateB->Resize(80, 40);
    CalculateB->SetTextColor(TColor::RGB2Pixel(255, 255, 255));
    CalculateB->SetBackgroundColor(TColor::RGB2Pixel(34, 151, 159));
    CalculateB->Associate(this);

	DrawPminFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(DrawPminFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	DrawPminText = new TGTextEntry(DrawPminFrame, new TGTextBuffer(100), 10000);
	DrawPminText->SetText("P(min) = ");
	DrawPminFrame->AddFrame(DrawPminText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	DrawPminText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	DrawPminText->SetAlignment(kTextCenterX);
	DrawPminText->Resize(140, 40);
	DrawPminText->SetEnabled(kFALSE);
	DrawPminText->SetFrameDrawn(kFALSE);
	DrawPminText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	DrawPminText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	DrawPminNumber = new TGNumberEntry(DrawPminFrame, 0, 0, TGNumberFormat::kNESInteger);
	DrawPminFrame->AddFrame(DrawPminNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	DrawPminNumber->GetButtonUp()->ChangeOptions(DrawPminNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	DrawPminNumber->GetButtonDown()->ChangeOptions(DrawPminNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	DrawPminNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	DrawPminNumber->Resize(100, 40);
	DrawPminNumber->SetNumber(0);
	DrawPminNumber->Associate(this);

	DrawPmaxFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(DrawPmaxFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	DrawPmaxText = new TGTextEntry(DrawPmaxFrame, new TGTextBuffer(100), 10000);
	DrawPmaxText->SetText("P(max) = ");
	DrawPmaxFrame->AddFrame(DrawPmaxText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	DrawPmaxText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	DrawPmaxText->SetAlignment(kTextCenterX);
	DrawPmaxText->Resize(140, 40);
	DrawPmaxText->SetEnabled(kFALSE);
	DrawPmaxText->SetFrameDrawn(kFALSE);
	DrawPmaxText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	DrawPmaxText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	DrawPmaxNumber = new TGNumberEntry(DrawPmaxFrame, 0, 0, TGNumberFormat::kNESInteger);
	DrawPmaxFrame->AddFrame(DrawPmaxNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	DrawPmaxNumber->GetButtonUp()->ChangeOptions(DrawPmaxNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	DrawPmaxNumber->GetButtonDown()->ChangeOptions(DrawPmaxNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	DrawPmaxNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	DrawPmaxNumber->Resize(100, 40);
	DrawPmaxNumber->SetNumber(2);
	DrawPmaxNumber->Associate(this);

	DrawAminFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(DrawAminFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	DrawAminText = new TGTextEntry(DrawAminFrame, new TGTextBuffer(100), 10000);
	DrawAminText->SetText("A(min) = ");
	DrawAminFrame->AddFrame(DrawAminText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	DrawAminText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	DrawAminText->SetAlignment(kTextCenterX);
	DrawAminText->Resize(140, 40);
	DrawAminText->SetEnabled(kFALSE);
	DrawAminText->SetFrameDrawn(kFALSE);
	DrawAminText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	DrawAminText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	DrawAminNumber = new TGNumberEntry(DrawAminFrame, 0, 0, TGNumberFormat::kNESInteger);
	DrawAminFrame->AddFrame(DrawAminNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	DrawAminNumber->GetButtonUp()->ChangeOptions(DrawAminNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	DrawAminNumber->GetButtonDown()->ChangeOptions(DrawAminNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	DrawAminNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	DrawAminNumber->Resize(100, 40);
	DrawAminNumber->SetNumber(1);
	DrawAminNumber->Associate(this);

	DrawAmaxFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(DrawAmaxFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	DrawAmaxText = new TGTextEntry(DrawAmaxFrame, new TGTextBuffer(100), 10000);
	DrawAmaxText->SetText("A(max) = ");
	DrawAmaxFrame->AddFrame(DrawAmaxText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	DrawAmaxText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	DrawAmaxText->SetAlignment(kTextCenterX);
	DrawAmaxText->Resize(140, 40);
	DrawAmaxText->SetEnabled(kFALSE);
	DrawAmaxText->SetFrameDrawn(kFALSE);
	DrawAmaxText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	DrawAmaxText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);
	DrawAmaxNumber = new TGNumberEntry(DrawAmaxFrame, 0, 0, TGNumberFormat::kNESInteger);
	DrawAmaxFrame->AddFrame(DrawAmaxNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	DrawAmaxNumber->GetButtonUp()->ChangeOptions(DrawAmaxNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	DrawAmaxNumber->GetButtonDown()->ChangeOptions(DrawAmaxNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	DrawAmaxNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	DrawAmaxNumber->Resize(100, 40);
	DrawAmaxNumber->SetNumber(5);
	DrawAmaxNumber->Associate(this);

	DrawYminFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(DrawYminFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	DrawYminText = new TGTextEntry(DrawYminFrame, new TGTextBuffer(100), 10000);
	DrawYminText->SetText("Y(min) = ");
	DrawYminFrame->AddFrame(DrawYminText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	DrawYminText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	DrawYminText->SetAlignment(kTextCenterX);
	DrawYminText->Resize(140, 40);
	DrawYminText->SetEnabled(kFALSE);
	DrawYminText->SetFrameDrawn(kFALSE);
	DrawYminText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	DrawYminText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	DrawYminNumber = new TGNumberEntry(DrawYminFrame, 0, 0, TGNumberFormat::kNESInteger);
	DrawYminFrame->AddFrame(DrawYminNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	DrawYminNumber->GetButtonUp()->ChangeOptions(DrawYminNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	DrawYminNumber->GetButtonDown()->ChangeOptions(DrawYminNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	DrawYminNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	DrawYminNumber->Resize(100, 40);
	DrawYminNumber->SetNumber(1.0E-6);
	DrawYminNumber->Associate(this);

	DrawYmaxFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(DrawYmaxFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	DrawYmaxText = new TGTextEntry(DrawYmaxFrame, new TGTextBuffer(100), 10000);
	DrawYmaxText->SetText("Y(max) = ");
	DrawYmaxFrame->AddFrame(DrawYmaxText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	DrawYmaxText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	DrawYmaxText->SetAlignment(kTextCenterX);
	DrawYmaxText->Resize(140, 40);
	DrawYmaxText->SetEnabled(kFALSE);
	DrawYmaxText->SetFrameDrawn(kFALSE);
	DrawYmaxText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	DrawYmaxText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);
	DrawYmaxNumber = new TGNumberEntry(DrawYmaxFrame, 0, 0, TGNumberFormat::kNESInteger);
	DrawYmaxFrame->AddFrame(DrawYmaxNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	DrawYmaxNumber->GetButtonUp()->ChangeOptions(DrawYmaxNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	DrawYmaxNumber->GetButtonDown()->ChangeOptions(DrawYmaxNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	DrawYmaxNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	DrawYmaxNumber->Resize(100, 40);
	DrawYmaxNumber->SetNumber(1.0E0);
	DrawYmaxNumber->Associate(this);

	DrawVBassFrame = new TGHorizontalFrame(ParameterFrame, 210, 40);
	ParameterFrame->AddFrame(DrawVBassFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	DrawVBassText = new TGTextEntry(DrawVBassFrame, new TGTextBuffer(100), 10000);
	DrawVBassText->SetText("V(Bass) = ");
	DrawVBassFrame->AddFrame(DrawVBassText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	DrawVBassText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	DrawVBassText->SetAlignment(kTextCenterX);
	DrawVBassText->Resize(140, 40);
	DrawVBassText->SetEnabled(kFALSE);
	DrawVBassText->SetFrameDrawn(kFALSE);
	DrawVBassText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	DrawVBassText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);
	DrawVBassNumber = new TGNumberEntry(DrawVBassFrame, 0, 0, TGNumberFormat::kNESInteger);
	DrawVBassFrame->AddFrame(DrawVBassNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	DrawVBassNumber->GetButtonUp()->ChangeOptions(DrawVBassNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	DrawVBassNumber->GetButtonDown()->ChangeOptions(DrawVBassNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	DrawVBassNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	DrawVBassNumber->Resize(100, 40);
	DrawVBassNumber->SetNumber(0.0);
	DrawVBassNumber->Associate(this);


	DrawButtonFrame = new TGHorizontalFrame(ParameterFrame, 240, 40);
	ParameterFrame->AddFrame(DrawButtonFrame, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	DrawButtonFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	DrawB = new TGTextButton(DrawButtonFrame, "Draw", DrawButton);
    DrawButtonFrame->AddFrame(DrawB, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 30, 0, 0, 0));
    DrawB->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
    DrawB->Resize(80, 40);
    DrawB->SetTextColor(TColor::RGB2Pixel(255, 255, 255));
    DrawB->SetBackgroundColor(TColor::RGB2Pixel(34, 151, 159));
    DrawB->Associate(this);

	CanvasFrame = new TGVerticalFrame(CalculateFrame, 890, 600);
	CalculateFrame->AddFrame(CanvasFrame, new TGLayoutHints(kLHintsTop | kLHintsRight, 0, 0, 0, 0));
	CanvasFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	FrameCanvas = new TRootEmbeddedCanvas("Hivap", CanvasFrame, 890, 600);
	CanvasFrame->AddFrame(FrameCanvas, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0));
	Int_t wid = FrameCanvas->GetCanvasWindowId();
	TCanvas *can  = new TCanvas("Canvas", 1780, 1200, wid);
	can->ToggleEventStatus();
	can->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "gui", this, "EventInfo(Int_t,Int_t,Int_t,TObject*)");
	FrameCanvas->AdoptCanvas(can);

//	ProgressBarFram = new TGHorizontalFrame(CalculateFrame, 790, 40);
//	CalculateFrame->AddFrame(ProgressBarFram, new TGLayoutHints(kLHintsTop | kLHintsRight, 0, 0, 0, 0));
	ProgressBar = new TGHProgressBar(CanvasFrame, TGProgressBar::kStandard, 890);
	CanvasFrame->AddFrame(ProgressBar, new TGLayoutHints(kLHintsTop | kLHintsRight, 0, 0, 0, 0));
	ProgressBar->ShowPosition();
	ProgressBar->SetWidth(890);
//	ProgressBar->SetSize(50);
	ProgressBar->SetBarColor("yellow");

	MapSubwindows();
	Resize();
	CenterOnParent();
	SetWindowName(name);
	MapWindow();
}

hivap::~hivap(){}

Bool_t hivap::ProcessMessage(Long_t msg,Long_t parm1, Long_t parm2)
{
	switch (GET_MSG(msg))
	{
		case kC_COMMAND:
			switch (GET_SUBMSG(msg))
			{
				case kCM_BUTTON:
					switch (parm1)
					{
						case CalculateButton:
						{
							ProjectileNNumber->GetNumberEntry()->SetTextColor(TColor::RGB2Pixel(0, 0, 0));
							if(Int_t(ProjectileZNumber->GetNumber())+Int_t(ProjectileNNumber->GetNumber()) != Int_t(ProjectileANumber->GetNumber()))
							{
								ProjectileNNumber->SetNumber(ProjectileANumber->GetNumber()-ProjectileZNumber->GetNumber());
								ProjectileNNumber->GetNumberEntry()->SetTextColor(TColor::RGB2Pixel(255, 0, 0));
							}
							TargetNNumber->GetNumberEntry()->SetTextColor(TColor::RGB2Pixel(0, 0, 0));
							if(Int_t(TargetZNumber->GetNumber())+Int_t(TargetNNumber->GetNumber()) != Int_t(TargetANumber->GetNumber()))
							{
								TargetNNumber->SetNumber(TargetANumber->GetNumber()-TargetZNumber->GetNumber());
								TargetNNumber->GetNumberEntry()->SetTextColor(TColor::RGB2Pixel(255, 0, 0));
							}
							if(ngraph_Draw>0)
							{	
								for(int i=0; i<ngraph_Draw; i++)
									delete []  HIVAP_cross_section[i];
								delete []  HIVAP_cross_section;
								delete [] name;
							}
							ngraph_Draw = Int_t(EvaporationProtonNumber->GetNumber()+1)*Int_t(EvaporationNeutronNumber->GetNumber()+1);
							nEnergyHivap = 0;
							nCrosssectionHivapTmp = 0;
							nCrosssectionHivap = 0;
							for(int i=0; i<100; i++)
							{
								HIVAP_Energy_Exp[i] = 0.0;
								HIVAP_Energy_cm[i] = 0.0;
							}
							
							name = new TString[ngraph_Draw];
							
							HIVAP_cross_section = new Double_t*[ngraph_Draw];
							for(int i=0; i<ngraph_Draw; i++)
							{
								name[i] = "";
					           	HIVAP_cross_section[i] = new Double_t[100];
            					memset(HIVAP_cross_section[i], 0, 100*sizeof(Double_t));
							}
							for(Double_t Ecm_tmp = EcmMinNumber->GetNumber(); Ecm_tmp<=EcmMaxNumber->GetNumber(); Ecm_tmp=Ecm_tmp+EcmDetENumber->GetNumber())
							{
								Float_t PositionValue = (1.0+(+Ecm_tmp - EcmMinNumber->GetNumber())/EcmDetENumber->GetNumber())/((EcmMaxNumber->GetNumber()-EcmMinNumber->GetNumber())/EcmDetENumber->GetNumber()+1.0);
								ProgressBar->SetPosition(100.0*PositionValue);
				//				std::cout <<Ecm_tmp << std::endl;
								MakeHivapInputfile(Ecm_tmp);
				//				std::cout <<Ecm_tmp << "   Make"<< std::endl;
								system("./Hivap/hivapn>>log.txt");
				//				std::cout <<Ecm_tmp << "   Calcula"<< std::endl;
								ReadExcitationFunction();
				//				std::cout <<Ecm_tmp << "   Read"<< std::endl;
							}
							Draw();
							
							break;
						}
						case DrawButton:
						{
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

void hivap::MakeHivapInputfile(Double_t Ecm_in)
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
                fileout << "  " << stmp << "  " << Int_t(ProjectileANumber->GetNumber()) <<"  ";
                filein >> stmp >> itmp;
                fileout << stmp << "  " << Int_t(ProjectileZNumber->GetNumber()) <<"  ";
                filein >> stmp >> itmp;
                fileout << stmp << "  " << Int_t(TargetANumber->GetNumber()) <<"  ";
                filein >> stmp >> itmp;
                fileout << stmp << "  " << Int_t(TargetZNumber->GetNumber()) <<"  ";
                getline(filein, stmp);
                fileout << std::endl;
                n++;
            }

            if(n==8)
            {
                filein >> stmp >> itmp;
                fileout << "  " << stmp << "  " << Int_t(EvaporationNeutronNumber->GetNumber() + 1) <<"  ";
                filein >> stmp >> itmp;
                fileout << stmp << "  " << Int_t(EvaporationProtonNumber->GetNumber() + 1) <<"  ";
                getline(filein, stmp);
                fileout << std::endl;
                n++;
            }
            if(n==22)
            {
                filein >> stmp >> dtmp;
                fileout << "  " << stmp << "  " << dtmp <<"  ";
                filein >> stmp >> dtmp;
                fileout << stmp << "  " << Af_AnNumber->GetNumber() <<"  ";
                filein >> stmp >> dtmp;
                fileout << stmp << "  " << CfNumber->GetNumber()  <<"  ";
                getline(filein, stmp);
                fileout << stmp << std::endl;
                n++;
            }
            if(n==31)
            {
                filein >> stmp >> dtmp;
                fileout << "  " << stmp << "  " << Ecm_in;
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

void hivap::ReadExcitationFunction()
{
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

		for(int i=0; i<2*Int_t(EvaporationProtonNumber->GetNumber() + 1); i++)
		{
    		getline(HIVAP_file, stmp);
		}
		getline(HIVAP_file, stmp);
		HIVAP_file>>stmp;
		HIVAP_file>>dtmp;
//		cout << "Cf = " << dtmp << endl;
		getline(HIVAP_file, stmp);
		for(int i=0; i<3*Int_t(EvaporationProtonNumber->GetNumber() + 1); i++)
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
                    		HIVAP_file >> HIVAP_Energy_Exp[nEnergyHivap] >> dtmp >> dtmp >> dtmp >> dtmp >> dtmp >> dtmp >> dtmp;
                        	getline(HIVAP_file, stmp);
                        	nEnergyHivap++;
                                //cout << nEnergyHivap-1 << "\t" << HIVAP_Energy_Exp[nEnergyHivap-1] <<endl;
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
        			for(int nz=0; nz<Int_t(EvaporationProtonNumber->GetNumber() + 1); nz++)
        			{
            			HIVAP_file >> stmp;
        				getline(HIVAP_file, stmp);
            			for(int i=0; i<Int_t(EvaporationNeutronNumber->GetNumber() + 1); i++)
            			{
							Int_t Z_Tmp = ProjectileZNumber->GetNumber() + TargetZNumber->GetNumber() - nz;
							Int_t A_Tmp = ProjectileANumber->GetNumber() + TargetANumber->GetNumber() - nz - (EvaporationNeutronNumber->GetNumber() - i);
							Int_t N_Tmp = A_Tmp - Z_Tmp;
							nuclear_data *dataTmp = new nuclear_data(Z_Tmp, A_Tmp, N_Tmp);
						//	HIVAP_file >> stmp;
						//	string sname1 = stmp.substr(0, 3);
						//	stmp.erase(stmp.begin(), stmp.begin()+3);
						//	Int_t Iname1 = stoi(sname1);
						//	TString Sname2 = stmp;
							Int_t Iname1 = A_Tmp;
							TString Sname2 = TString(dataTmp->getname());
							delete dataTmp;
							name[nz*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+i] = Form("^{%d}%s", Iname1, Sname2.Data());
				//			std::cout<<name[nz*Int_t(EvaporationNeutronNumber->GetNumber())+i]<<std::endl;
           //     			HIVAP_file >> name[nz*Int_t(EvaporationNeutronNumber->GetNumber())+i];
						}
            			getline(HIVAP_file, stmp);
            			nCrosssectionHivapTmp = nCrosssectionHivap;
            			while(1)
            			{
                			if(stmp.size()!=0)
                			{
                    			HIVAP_file.seekg(-stmp.size(), HIVAP_file.cur);
                    			HIVAP_file >> HIVAP_Energy_cm[nCrosssectionHivapTmp];
                    			for(int i=0; i<Int_t(EvaporationNeutronNumber->GetNumber() +1 ); i++)
                    			{
                        			HIVAP_file >> HIVAP_cross_section[nz*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+i][nCrosssectionHivapTmp];
                    			}
                    			getline(HIVAP_file, stmp);
                    			nCrosssectionHivapTmp++;
                    			getline(HIVAP_file, stmp);
                			}
                			else
                    			break;
            			}
        			}
        			nCrosssectionHivap = nCrosssectionHivapTmp;
				}
  			}
        }
	}
	else
		std::cout << "Cannot open ./Hivap/hivaperg.dat" << std::endl;
	HIVAP_file.close();
}

void hivap::Draw()
{
	CrossSectionExpVe.clear();
	CrossSectionExp CrossSectionExpTmp;
	ifstream FinCrossSectionExp;
	FinCrossSectionExp.open("./data/cross-section.txt");
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
								 >> CrossSectionExpTmp.Facility >> CrossSectionExpTmp.Cf
								 >> CrossSectionExpTmp.Af_An)
		{
			CrossSectionExpVe.push_back(CrossSectionExpTmp);
//			std::cout << CrossSectionExpTmp.CrossSectionub << std::endl;
		}
//		std::cout << CrossSectionExpVe.size() << std::endl; 
	}
	else
		std::cout << "Cannot open ./data/cross-section.txt " << std::endl;
	FinCrossSectionExp.close();
	Int_t nDraw = (EvaporationProtonNumber->GetNumber() + 1)*(EvaporationNeutronNumber->GetNumber() + 1);
	TGraphErrors *Exp[nDraw];
	Int_t* Exp_np = new Int_t[nDraw];
	TGraphErrors *HIVAP[nDraw];
	Int_t* HIVAP_np = new Int_t[nDraw];
	for(int i=0; i<nDraw; i++)
	{
		HIVAP[i] = new TGraphErrors;
		HIVAP_np[i] = 0;
		Exp[i] = new TGraphErrors;
		Exp_np[i] = 0;
	}
	DrawYmaxNumber->SetNumber(1.0E-9);
	if(DrawPmaxNumber->GetNumber() > EvaporationProtonNumber->GetNumber())
	{
		DrawPmaxNumber->SetNumber(EvaporationProtonNumber->GetNumber());
		std::cout << "\033[31m Input Error of P(max) \033[0m" << std::endl;
	}
	if(DrawPminNumber->GetNumber() < 0)
	{
		DrawPminNumber->SetNumber(0);
		std::cout << "\033[31m Input Error of P(min) \033[0m" << std::endl;
	}
	for(int i=DrawPminNumber->GetNumber(); i<=DrawPmaxNumber->GetNumber(); i++)
	{
    	for(int jj=DrawAmaxNumber->GetNumber(); jj>=DrawAminNumber->GetNumber(); jj--)
    	{
			int j = EvaporationNeutronNumber->GetNumber()  - (jj -i);
			if(j >= EvaporationNeutronNumber->GetNumber() || j < 0)	continue;
			for(auto it = CrossSectionExpVe.begin(); it != CrossSectionExpVe.end();)
			{
				Int_t A_Tmp = ProjectileANumber->GetNumber() + TargetANumber->GetNumber() - i - (EvaporationNeutronNumber->GetNumber() - j);
				if(it->Zp == ProjectileZNumber->GetNumber() && it->Ap == ProjectileANumber->GetNumber() &&
				   it->Zt == TargetZNumber->GetNumber()     && it->At == TargetANumber->GetNumber()  &&
				   it->ZFER == ProjectileZNumber->GetNumber() + TargetZNumber->GetNumber() - i && 
				   it->AFER == A_Tmp)
				{
					Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() +1)+j]->SetPoint(Exp_np[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j], it->BeamEnergy, it->CrossSectionub);
					Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetPointError(Exp_np[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j], 0.0, it->ErrCrossSectionub);
					Exp_np[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]++;
		//		cout << it->Zp << "\t" << it->Ap << "\t" << it->Zt << "\t" << it->At << "\t" << it->BeamEnergy << "\t" << it->CrossSectionub <<"\t" << it->ErrCrossSectionub << std::endl; 
				}
				it++;
			}
        	for(int k=0; k<100; k++)
        	{
            	if(HIVAP_Energy_cm[k]>0)
            	{
                	if(k > 0 && HIVAP_cross_section[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j][k]*1E3 < DrawYminNumber->GetNumber() && HIVAP_cross_section[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j][k-1]*1E3 > DrawYminNumber->GetNumber())                 
						break;
                	if(HIVAP_cross_section[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j][k]*1E3 > DrawYminNumber->GetNumber())
                	{
                    	HIVAP[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetPoint(HIVAP_np[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j], HIVAP_Energy_Exp[k], HIVAP_cross_section[i*Int_t(EvaporationNeutronNumber->GetNumber() +1)+j][k]*1000.0);
                    	HIVAP_np[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]++;
						if(DrawYmaxNumber->GetNumber() < HIVAP_cross_section[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j][k]*1000.0)
							DrawYmaxNumber->SetNumber(HIVAP_cross_section[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j][k]*1000.0);
                	}
            	}
        	}
    	}

	}
	DrawYmaxNumber->SetNumber(DrawYmaxNumber->GetNumber()*3.0);
	for(int i=0; i<9; i++)
	{
		if(Int_t(DrawYmaxNumber->GetNumber()*pow(10.0, i)) >0)
		{
				DrawYmaxNumber->SetNumber(Int_t(DrawYmaxNumber->GetNumber()*pow(10.0, i))/(pow(10.0, i)));
				break;
		}
	}
	Int_t ngraph = 0;

    for(int jj=DrawAmaxNumber->GetNumber(); jj >= DrawAminNumber->GetNumber(); jj--)
    {
		for(int i=DrawPminNumber->GetNumber(); i<=DrawPmaxNumber->GetNumber(); i++)
		{
			int j = EvaporationNeutronNumber->GetNumber() - (jj -i);
			if(j >= EvaporationNeutronNumber->GetNumber() || j < 0)	continue;
        	if(HIVAP_np[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j] > 2)
        	{
	
            	if(ngraph < 11)
            	{
                	HIVAP[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetMarkerStyle(20 + ngraph);
                	Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetMarkerStyle(20 + ngraph);
            	}
            	else if(ngraph <= 22)
            	{
                	HIVAP[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetMarkerStyle(9+ngraph);
                	Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetMarkerStyle(9+ngraph);
            	}
            	else if(ngraph <= 33)
            	{
                	HIVAP[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetMarkerStyle(ngraph-2);
                	Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetMarkerStyle(ngraph-2);
            	}
            	HIVAP[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetMarkerSize(1.0);
            	Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetMarkerSize(1.0);
				Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetMarkerColor(kRed);
				Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetLineColor(kRed);
            	if(ngraph < 11)
            	{
					if(ngraph+3==5)
					{
						HIVAP[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetMarkerColor(96);
						HIVAP[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetLineColor(96);
						Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetMarkerColor(96);
						Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetLineColor(96);
					}
                	else if(ngraph+3 == 10) 
					{
						HIVAP[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetMarkerColor(50);
						HIVAP[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetLineColor(50);
						Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetMarkerColor(50);
						Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetLineColor(50);
					}
                	else 
					{
						HIVAP[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetMarkerColor(ngraph+3);
						HIVAP[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetLineColor(ngraph+3);
						Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetMarkerColor(ngraph+3);
						Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetLineColor(ngraph+3);
					}
            	}
            	else
            	{
                	HIVAP[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetMarkerColor(3*ngraph+3);
                	HIVAP[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetLineColor(3*ngraph+3);
					Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetMarkerColor(3*ngraph+3);
					Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetLineColor(3*ngraph+3);
            	}
            	HIVAP[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetLineStyle(7);
            	HIVAP[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetLineWidth(2);
				HIVAP[i*Int_t(EvaporationNeutronNumber->GetNumber()+ 1)+j]->SetMarkerSize(1.5);
            	Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetLineStyle(1);
            	Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetLineWidth(2);
				Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]->SetMarkerSize(1.5);
//				std::cout << i << "\t" << j << "\t" << HIVAP[i*Int_t(EvaporationNeutronNumber->GetNumber())+j]->GetMarkerStyle() << "\t" << Exp[i*Int_t(EvaporationNeutronNumber->GetNumber())+j]->GetMarkerStyle() << endl; 
            	ngraph++;
        	}
    	}
	}
	        
	TMultiGraph *mg = new TMultiGraph();		
	TLegend *leg = new TLegend(0.84, 0.1, 0.999, 0.9);

//			std::cout <<" P   A  N   j"<<std::endl;
	for(int i=Int_t(DrawPminNumber->GetNumber()); i<=Int_t(DrawPmaxNumber->GetNumber()); i++)
	{
    	for(int jj=Int_t(DrawAmaxNumber->GetNumber()); jj>=Int_t(DrawAminNumber->GetNumber()); jj--)
    	{
			int j = EvaporationNeutronNumber->GetNumber() - (jj - i);
			if(j >= EvaporationNeutronNumber->GetNumber() || j < 0)	continue;
	//		std::cout << i << "\t" << j << std::endl;
        	if(HIVAP_np[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j] > 2)
        	{
            	mg->Add(HIVAP[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j], "C");
            	leg->AddEntry(HIVAP[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j], name[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j]);
//				std::cout << i <<"  " <<jj <<"  " <<jj-i <<"   "<< j << " "<< std::endl;
				if(Exp_np[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j] > 0)
					mg->Add(Exp[i*Int_t(EvaporationNeutronNumber->GetNumber() + 1)+j], "PL");
        	}
    	}
	}
	TString MgName;
	nuclear_data *Projectile_data = new nuclear_data(Int_t(ProjectileZNumber->GetNumber()), Int_t(ProjectileANumber->GetNumber()), Int_t(ProjectileNNumber->GetNumber()));
	nuclear_data *Target_data = new nuclear_data(Int_t(TargetZNumber->GetNumber()), Int_t(TargetANumber->GetNumber()), Int_t(TargetNNumber->GetNumber()));
	nuclear_data *Fusion_data = new nuclear_data(Int_t(ProjectileZNumber->GetNumber()+TargetZNumber->GetNumber()), Int_t(ProjectileANumber->GetNumber()+TargetANumber->GetNumber()), Int_t(ProjectileNNumber->GetNumber()+TargetNNumber->GetNumber()));
	TString Projectile_name = Projectile_data->getname();
	TString target_name = Target_data->getname();
	TString Fusion_name = Fusion_data->getname();
	MgName.Form("^{%d}%s + ^{%d}%s #rightarrow ^{%d}%s^{*} (Cf = %0.2f)", Int_t(ProjectileANumber->GetNumber()), Projectile_name.Data(), Int_t(TargetANumber->GetNumber()), target_name.Data(), Int_t(ProjectileANumber->GetNumber()+TargetANumber->GetNumber()), Fusion_name.Data(), CfNumber->GetNumber());

	mg->SetTitle(Form("%s; Beam Energy [MeV]; Cross section [#mub]", MgName.Data()));
	mg->GetYaxis()->CenterTitle("1");
	mg->GetXaxis()->CenterTitle("1");
	mg->GetXaxis()->SetTitleOffset(1.4);
	mg->GetYaxis()->SetTitleOffset(1.4);
	mg->GetYaxis()->SetRangeUser(DrawYminNumber->GetNumber(), DrawYmaxNumber->GetNumber());

	Double_t VBassValue = 1.44*(1.0 + Projectile_data->getmass()/Target_data->getmass())*((ProjectileZNumber->GetNumber()*TargetZNumber->GetNumber())/(1.16*(pow(ProjectileANumber->GetNumber(), 1.0/3.0)+pow(TargetANumber->GetNumber(), 1.0/3.0)+2.0)));
	DrawVBassNumber->SetNumber(VBassValue);

	delete Projectile_data;
	delete Target_data;
	delete Fusion_data;	
	TArrow* acb = new TArrow(DrawVBassNumber->GetNumber(), 10*DrawYminNumber->GetNumber(), DrawVBassNumber->GetNumber(), DrawYminNumber->GetNumber(), 0.02,"|>");
	acb->SetAngle(30);
	acb->SetLineWidth(2);
	acb->SetLineColor(1);
	acb->SetFillColor(1);
	TLatex *texta = new TLatex(DrawVBassNumber->GetNumber()-5, 18*DrawYminNumber->GetNumber(), "B_{Bass}");
	TCanvas *DrawCanvastmp = FrameCanvas->GetCanvas();
	DrawCanvastmp->ToggleEventStatus();
	DrawCanvastmp->cd();
//	FrameCanvas->cd();
	mg->Draw("A");
	leg->SetTextFont(22);
	leg->SetTextSize(0.04);
	leg->SetMargin(0.6);
	leg->Draw();
	acb->Draw();
	texta->Draw();
	DrawCanvastmp->SetLogy(1);
//	DrawCanvastmp->Modified();
	DrawCanvastmp->Update();
//	FrameCanvas->SetLogy(1);
//	FrameCanvas->Modified();
//	FrameCanvas->Update();
//	delete [] HIVAP_np;
//	for(int i=0; i<nDraw; i++)
//			delete HIVAP[i];
//	delete mg;
//	delete leg;
//	delete acb;
}


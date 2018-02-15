void drratio()
{
//=========Macro generated from canvas: c1_n52/c1_n52
//=========  (Mon Mar 20 11:19:04 2017) by ROOT version6.04/00
   TCanvas *c1_n52 = new TCanvas("c1_n52", "c1_n52",0,0,700,500);
   gStyle->SetOptStat(0);
   c1_n52->SetHighLightColor(2);
   c1_n52->Range(0,0,1,1);
   c1_n52->SetFillColor(0);
   c1_n52->SetBorderMode(0);
   c1_n52->SetBorderSize(2);
   c1_n52->SetFrameBorderMode(0);
   
   TH2D *drratio1_vs_z__8 = new TH2D("drratio1_vs_z__8","Outside/Internal Dose Rate ratio",201,0,201,100,0,2e-05);
   drratio1_vs_z__8->SetBinContent(5073,12000);
   drratio1_vs_z__8->SetBinContent(10048,12000);
   drratio1_vs_z__8->SetBinContent(11978,12000);
   drratio1_vs_z__8->SetEntries(36000);
   drratio1_vs_z__8->GetXaxis()->SetTitle("z source (cm)");
   drratio1_vs_z__8->GetXaxis()->SetLabelFont(42);
   drratio1_vs_z__8->GetXaxis()->SetLabelSize(0.035);
   drratio1_vs_z__8->GetXaxis()->SetTitleSize(0.035);
   drratio1_vs_z__8->GetXaxis()->SetTitleFont(42);
   drratio1_vs_z__8->GetYaxis()->SetTitle("Ratio");
   drratio1_vs_z__8->GetYaxis()->SetLabelFont(42);
   drratio1_vs_z__8->GetYaxis()->SetLabelSize(0.035);
   drratio1_vs_z__8->GetYaxis()->SetTitleSize(0.035);
   drratio1_vs_z__8->GetYaxis()->SetTitleFont(42);
   drratio1_vs_z__8->GetZaxis()->SetLabelFont(42);
   drratio1_vs_z__8->GetZaxis()->SetLabelSize(0.035);
   drratio1_vs_z__8->GetZaxis()->SetTitleSize(0.035);
   drratio1_vs_z__8->GetZaxis()->SetTitleFont(42);
   drratio1_vs_z__8->Draw("");
   
   TH2D *drratio2_vs_z__9 = new TH2D("drratio2_vs_z__9","Outside/Internal Dose Rate ratio",201,0,201,100,0,2e-05);
   drratio2_vs_z__9->SetBinContent(4873,12000);
   drratio2_vs_z__9->SetBinContent(10048,12000);
   drratio2_vs_z__9->SetBinContent(12178,12000);
   drratio2_vs_z__9->SetEntries(36000);
   drratio2_vs_z__9->SetLineColor(2);
   drratio2_vs_z__9->SetMarkerColor(2);
   drratio2_vs_z__9->GetXaxis()->SetLabelFont(42);
   drratio2_vs_z__9->GetXaxis()->SetLabelSize(0.035);
   drratio2_vs_z__9->GetXaxis()->SetTitleSize(0.035);
   drratio2_vs_z__9->GetXaxis()->SetTitleFont(42);
   drratio2_vs_z__9->GetYaxis()->SetLabelFont(42);
   drratio2_vs_z__9->GetYaxis()->SetLabelSize(0.035);
   drratio2_vs_z__9->GetYaxis()->SetTitleSize(0.035);
   drratio2_vs_z__9->GetYaxis()->SetTitleFont(42);
   drratio2_vs_z__9->GetZaxis()->SetLabelFont(42);
   drratio2_vs_z__9->GetZaxis()->SetLabelSize(0.035);
   drratio2_vs_z__9->GetZaxis()->SetTitleSize(0.035);
   drratio2_vs_z__9->GetZaxis()->SetTitleFont(42);
   drratio2_vs_z__9->Draw("same");
   
   TLegend *leg = new TLegend(-2.353437e-185,-2.353437e-185,-2.353437e-185,-2.353437e-185,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("drratio1_vs_z","Detector 1 (z=0 cm)","lp");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("drratio2_vs_z","Detector 2 (z=200 cm)","lp");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   c1_n52->Modified();
   c1_n52->cd();
   c1_n52->SetSelected(c1_n52);
}

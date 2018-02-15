void drin_1m()
{
//=========Macro generated from canvas: c1_n56/c1_n56
//=========  (Mon Mar 20 11:19:04 2017) by ROOT version6.04/00
   TCanvas *c1_n56 = new TCanvas("c1_n56", "c1_n56",0,0,700,500);
   gStyle->SetOptStat(0);
   c1_n56->SetHighLightColor(2);
   c1_n56->Range(0,0,1,1);
   c1_n56->SetFillColor(0);
   c1_n56->SetBorderMode(0);
   c1_n56->SetBorderSize(2);
   c1_n56->SetFrameBorderMode(0);
   
   TH2D *drin1_1m_vs_z__17 = new TH2D("drin1_1m_vs_z__17","Internal Dose Rate, 1m avg, 2m distance",201,0,201,100,0,20000);
   drin1_1m_vs_z__17->SetBinContent(5276,10);
   drin1_1m_vs_z__17->SetBinContent(8424,10);
   drin1_1m_vs_z__17->SetBinContent(10760,10);
   drin1_1m_vs_z__17->SetEntries(30);
   drin1_1m_vs_z__17->GetXaxis()->SetTitle("z source (cm)");
   drin1_1m_vs_z__17->GetXaxis()->SetLabelFont(42);
   drin1_1m_vs_z__17->GetXaxis()->SetLabelSize(0.035);
   drin1_1m_vs_z__17->GetXaxis()->SetTitleSize(0.035);
   drin1_1m_vs_z__17->GetXaxis()->SetTitleFont(42);
   drin1_1m_vs_z__17->GetYaxis()->SetTitle("Dose rate (#muSv/h)");
   drin1_1m_vs_z__17->GetYaxis()->SetLabelFont(42);
   drin1_1m_vs_z__17->GetYaxis()->SetLabelSize(0.035);
   drin1_1m_vs_z__17->GetYaxis()->SetTitleSize(0.035);
   drin1_1m_vs_z__17->GetYaxis()->SetTitleFont(42);
   drin1_1m_vs_z__17->GetZaxis()->SetLabelFont(42);
   drin1_1m_vs_z__17->GetZaxis()->SetLabelSize(0.035);
   drin1_1m_vs_z__17->GetZaxis()->SetTitleSize(0.035);
   drin1_1m_vs_z__17->GetZaxis()->SetTitleFont(42);
   drin1_1m_vs_z__17->Draw("");
   
   TH2D *drin2_1m_vs_z__18 = new TH2D("drin2_1m_vs_z__18","Internal Dose Rate, 1m avg, 2m distance",201,0,201,100,0,20000);
   drin2_1m_vs_z__18->SetBinContent(5076,10);
   drin2_1m_vs_z__18->SetBinContent(8424,10);
   drin2_1m_vs_z__18->SetBinContent(10960,10);
   drin2_1m_vs_z__18->SetEntries(30);
   drin2_1m_vs_z__18->SetLineColor(2);
   drin2_1m_vs_z__18->SetMarkerColor(2);
   drin2_1m_vs_z__18->GetXaxis()->SetLabelFont(42);
   drin2_1m_vs_z__18->GetXaxis()->SetLabelSize(0.035);
   drin2_1m_vs_z__18->GetXaxis()->SetTitleSize(0.035);
   drin2_1m_vs_z__18->GetXaxis()->SetTitleFont(42);
   drin2_1m_vs_z__18->GetYaxis()->SetLabelFont(42);
   drin2_1m_vs_z__18->GetYaxis()->SetLabelSize(0.035);
   drin2_1m_vs_z__18->GetYaxis()->SetTitleSize(0.035);
   drin2_1m_vs_z__18->GetYaxis()->SetTitleFont(42);
   drin2_1m_vs_z__18->GetZaxis()->SetLabelFont(42);
   drin2_1m_vs_z__18->GetZaxis()->SetLabelSize(0.035);
   drin2_1m_vs_z__18->GetZaxis()->SetTitleSize(0.035);
   drin2_1m_vs_z__18->GetZaxis()->SetTitleFont(42);
   drin2_1m_vs_z__18->Draw("same");
   
   TLegend *leg = new TLegend(-2.353437e-185,-2.353437e-185,-2.353437e-185,-2.353437e-185,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("drin1_1m_vs_z","Detector 1 (z=0 cm)","lp");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("drin2_1m_vs_z","Detector 2 (z=200 cm)","lp");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   c1_n56->Modified();
   c1_n56->cd();
   c1_n56->SetSelected(c1_n56);
}

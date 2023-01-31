#include <wx/wx.h>
#include <iostream>
#include <string>
using namespace std;

const int MONEY_VALUES[] = { 100, 50, 20, 10, 5, 2, 1 }; // values of money in ribu rupiah
const int NUM_MONEY = 7; // number of money types

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);
    void OnCompute(wxCommandEvent& event);

private:
    wxTextCtrl* input, * output;
    int ChangeCoins(int amount, int count[]);
};

MainFrame::MainFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxPoint(50, 50), wxSize(500, 300)) {
    wxPanel* panel = new wxPanel(this, -1);
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* st1 = new wxStaticText(panel, -1, "Jumlah uang (dalam satuan ribu rupiah):",
        wxPoint(10, 10), wxSize(150, 25));
    input = new wxTextCtrl(panel, -1, "", wxPoint(160, 10), wxSize(150, 25));

    wxStaticText* st2 = new wxStaticText(panel, -1, "Nilai Tukar:", wxPoint(10, 50),
        wxSize(150, 25));
    output = new wxTextCtrl(panel, -1, "", wxPoint(160, 50), wxSize(150, 25),
        wxTE_MULTILINE | wxTE_READONLY);

    wxButton* compute =
        new wxButton(panel, wxID_EXIT, "Hitung", wxPoint(160, 90), wxSize(75, 30));
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(MainFrame::OnCompute));

    hbox1->Add(st1, 1, wxLEFT | wxTOP, 10);
    hbox1->Add(input, 1, wxLEFT | wxTOP, 10);
    hbox2->Add(st2, 1, wxLEFT | wxTOP, 10);
    hbox2->Add(output, 1, wxLEFT | wxTOP, 10);
    vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    vbox->Add(hbox2, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    vbox->Add(compute, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    panel->SetSizer(vbox);
    Centre();
}

int MainFrame::ChangeCoins(int amount, int count[]) {
    int result = 0;
    for (int i = 0; i < NUM_MONEY; i++) {
        count[i] = amount / MONEY_VALUES[i];
        result += count[i];
        amount %= MONEY_VALUES[i];
    }
    return result;
}

void MainFrame::OnCompute(wxCommandEvent& event) {
    long amount = 0;
    input->GetValue().ToLong(&amount);
    int count[NUM_MONEY];
    int totalCoins = ChangeCoins(amount, count);
    output->SetValue("");
    for (int i = 0; i < NUM_MONEY; i++) {
        output->AppendText(wxString::Format("%d x %d ribu\n", count[i], MONEY_VALUES[i]));
    }
    output->AppendText(wxString::Format("Total: %d lembar", totalCoins));
}

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

bool MyApp::OnInit() {
    MainFrame* frame = new MainFrame("GCashier");
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp);

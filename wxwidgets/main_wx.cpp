#include <wx/wx.h>

class Simple : public wxFrame {
public:
    Simple(const wxString& title);
};

Simple::Simple(const wxString& title) :
    wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150)) {
	Centre();
}

class MyApp: public wxApp {
public:
    virtual bool OnInit();
};

bool MyApp::OnInit() {
    Simple *simple = new Simple(wxT("Simple"));
    simple->Show(true);   // старт петли обработки событий
    return true;
}

IMPLEMENT_APP(MyApp)   // этот макрос реализует функцию main() в приложениях wxWidgets,
                                            // скрывая подробности главного цикла ожидания события.
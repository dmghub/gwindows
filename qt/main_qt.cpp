#include <qapplication.h>
#include <qdialog.h>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QDialog startDialog;
    startDialog.setMinimumWidth(300);
    startDialog.show();
    return app.exec();
}
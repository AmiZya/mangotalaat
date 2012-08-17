#include "ui/mainwindow.h"
#include "ui/loggindialog.h"

#include "mangoapp.h"

int main(int argc, char *argv[])
{
    MangoApp application(argc, argv);

#if defined(DEBUG)
    // ask for authentication
    LogginDialog dialog;
    dialog.exec();

    if ( !dialog.isAccepted() ) {
        QMessageBox::warning(0, "Invalid Data", "username and password is not correct"
                             " ,System will closed now!");
        return (0);
    }
    int userId = dialog.getUserID();
#else
    int userId = 1;
#endif

    MainWindow w(userId);
    w.show();

    return application.exec();
}



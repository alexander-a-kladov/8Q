#include <qapplication.h>
#include "form8q.h"

int width0,height0;

int main(int argc, char **argv)
{
    QApplication app(argc,argv);
    
    if (argc>1) {
	width0 = height0 = atoi(argv[1]);
    } else width0 = height0 = 216;
    
    FormQ8 form8;
    form8.show();
    app.exec();
    return 0;
}

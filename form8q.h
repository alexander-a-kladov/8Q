#include <qframe.h>
#include <qpixmap.h>
#include <qpainter.h>

#ifndef __FORM_8Q_H__
#define __FORM_8Q_H__

extern int width0, height0;

class FormQ8 : public QFrame
{
Q_OBJECT
public:
    FormQ8(QWidget *parent=0,const char* name=0)
    {
	q=0;
	backgr=NULL;
	setFixedSize(width0,height0);
	backgr = new QPixmap(width(),height());
	backgr1 = new QPixmap(width(),height());
	backgr->fill(Qt::white);
	QPainter p(backgr);
	p.setBrush(QBrush(Qt::red));
	p.setPen(Qt::NoPen);
	for (int i=0;i<8;i++)
	for (int j=0;j<4;j++)
	    p.drawRect(j*(width()/4)+(i%2)*width()/8,i*(height()/8),width()/8,height()/8);
	//setErasePixmap(*backgr);
	p.end();
	QPainter p1(backgr1);
	p1.drawPixmap(0,0,*backgr);
	p1.end();
	showInfo();
	setWindowTitle("8Q - Let's go");
    };
    
    int min(int v1, int v2)
    {
	if (v1<=v2) return v1;
	else return v2;
    }
protected:
    int q;
    QPixmap *backgr,*backgr1;
    QPoint mas[8];
    void mousePressEvent(QMouseEvent *ev);
    void paintEvent(QPaintEvent *ev);
    int  num_point_fill(int r, int c);
    void drawFZ(int r, int c);
    void drawQ(int r, int c);
    void showInfo();
    bool is_this_point_enable(int r, int c);
};


#endif

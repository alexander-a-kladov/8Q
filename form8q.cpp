#include "form8q.h"
#include <QMouseEvent>

int FormQ8::num_point_fill(int r, int c)
{
    QPoint pt(c,r);
//    cout << "is_point_fill?" << endl;
    for (int i=0;i<q;i++)
    {
	if (pt==mas[i]) return i;
    }
    return -1;
}

bool FormQ8::is_this_point_enable(int r, int c)
{
    QPoint pt(c,r);
    for (int i=0;i<q;i++)
    if ((pt.x()==mas[i].x())||(pt.y()==mas[i].y())||(abs(pt.x()-mas[i].x())==abs(pt.y()-mas[i].y()))) return false;
    return true;
}

void FormQ8::showInfo()
{
    QPainter p(backgr1);
    QFont font=p.font();
    font.setBold(true);
    p.setFont(font);
    p.drawText(0,0,width(),height(), Qt::AlignCenter,"Eight Queens Game\nMouse Button Control\n");
//    p.drawText(0,52,width(),25, Qt::AlignCenter,"Left/Right Button");
    p.end();
    repaint();
    return;
}

void FormQ8::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    p.drawPixmap(0,0,*backgr1);
    return;
}

void FormQ8::drawQ(int r, int c)
{
    QPainter p(backgr1);
    p.setBrush(QBrush(Qt::blue));
    p.setPen(Qt::NoPen);
    p.drawEllipse(c*(width()/8)+2,r*(height()/8)+2,width()/8-4,height()/8-4);
    return;
}

void FormQ8::drawFZ(int r, int c)
{
    int v1,v2,v;
    QPainter p(backgr1);
    p.setPen(QPen(Qt::black,3));
    p.drawLine(0,r*(height()/8)+height()/16,width(),r*(height()/8)+height()/16);
    p.drawLine(c*(width()/8)+width()/16,0,c*(width()/8)+width()/16,height());
    v1 = 8-c;v2 = r;v = min(v1,v2);
    p.drawLine(c*(width()/8)+width()/16,r*(height()/8)+height()/16,
		(c+v+1)*(width()/8),(r-v)*(height()/8));
    v1 = 8-c;v2 = 8-r;v = min(v1,v2);
    p.drawLine(c*(width()/8)+width()/16,r*(height()/8)+height()/16,
		(c+v+1)*(width()/8),(r+v+1)*(height()/8));
    v1 = c;v2 = 8-r;v = min(v1,v2);
    p.drawLine(c*(width()/8)+width()/16,r*(height()/8)+height()/16,
		(c-v)*(width()/8),(r+v+1)*(height()/8));
    v1 = c;v2 = r;v = min(v1,v2);
    p.drawLine(c*(width()/8)+width()/16,r*(height()/8)+height()/16,
		(c-v)*(width()/8),(r-v)*(height()/8));
    return;
}

void FormQ8::mousePressEvent(QMouseEvent *ev)
{
    int r,c,num;
    c = ev->x()/(width()/8);
    r = ev->y()/(height()/8);
    switch(ev->button()) 
    {
    case Qt::LeftButton:
    case Qt::RightButton:
    if (q==0) {
	QPainter p(backgr1);
	p.drawPixmap(0,0,*backgr); // clear
    }
    
    if ((num=num_point_fill(r,c))!=-1) { // Стираем если можем
	QPainter p(backgr1);
	p.drawPixmap(0,0,*backgr);
	p.end();
    if (q>0) {mas[num]=mas[q-1];q--;}
    for (int i=0;i<q;i++) {
	drawFZ(mas[i].y(),mas[i].x());
	drawQ(mas[i].y(),mas[i].x());
    }
    if (q==0) showInfo();
	repaint();
    }
    else  // Если не можем стиреть рисуем
    if (is_this_point_enable(r,c)) {
    drawFZ(r,c);
    drawQ(r,c);
	repaint();
    mas[q]=QPoint(c,r);
    q++;
    } else {
//	cout << "not allowed" << endl;
    }
    break;
/*    case Qt::RightButton: 
    if ((num=num_point_fill(r,c))!=-1) {
    bitBlt(backgr1,0,0,backgr,0,0,width(),height());
    if (q>0) {mas[num]=mas[q-1];q--;}
    for (int i=0;i<q;i++) {
	drawFZ(mas[i].y(),mas[i].x());
	drawQ(mas[i].y(),mas[i].x());
    }
    if (q==0) showInfo();
    setErasePixmap(*backgr1);
    }
    break;
*/
    default:
    break;
    }
    QString qs;
    if (q==0) setWindowTitle("8Q - Let's go");
    else if (q==8) setWindowTitle("8Q - You Win!");
    else setWindowTitle(qs.sprintf("%dQ",q));
    return;
}

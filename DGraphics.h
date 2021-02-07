
void DSetColor(double r, double g, double b, double a)
{
    double mmx = 255;
    if (r > mmx)
        r = mmx;
    if (g > mmx)
        g = mmx;
    if (b > mmx)
        b = mmx;
    r /= mmx;
    g /= mmx;
    b /= mmx;
    glColor4f(r, g, b, a);
}

void DCircle(int x,int y,int r,int width)
{
    int i;
    for(i=r;i>r-width;i--)
    {
        iCircle(x,y,i);
    }
}

void DLine(int x1,int y1,int x2,int y2,int Width)
{
    int i;
    for(i=x1;i<=x2;i++)
    {
        iPoint(i,((y2-y1)*(i-x1)*1.0/(x2-x1))+y1,Width);
    }

    for(i=y1;i<=y2;i++)
    {
        iPoint(((x2-x1)*(i-y1)*1.0/(y2-y1))+x1,i,Width);
    }
}


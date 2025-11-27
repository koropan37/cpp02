#include "Point.hpp"

//ベクトルの外戚を求める式
//(vec{u} = (x_u, y_u),vec{v} = (x_v, y_v))
//CrossProduct = x_u * y_v - y_u * x_v
//ABとAPの外積を計算
static Fixed cross_product(Point const a, Point const b, Point p) {
    Fixed ab_x = b.getX() - a.getX();
    Fixed ab_y = b.getY() - a.getY();
    Fixed ap_x = p.getX() - a.getX();
    Fixed ap_y = p.getY() - a.getY();
    return ((ab_x * ap_y) - (ab_y * ap_x));
}

bool bsp( Point const a, Point const b, Point const c, Point const p) {
	Fixed ab_ap = cross_product(a, b, p);
    Fixed bc_bp = cross_product(b, c, p);
    Fixed ca_cp = cross_product(c, a, p);
    
    if(ab_ap == 0 || bc_bp == 0 || ca_cp == 0) return false;

    return ((ab_ap > 0 && bc_bp > 0 && ca_cp > 0) 
            || (ab_ap < 0 && bc_bp < 0 && ca_cp < 0));
}

#include "PointLocationCalculator.h"

using fmWavMove::PointLocationCalculator;


bool PointLocationCalculator::IsPointInPolygon(geometry_msgs::Point p, geometry_msgs::Point polygon[])
{
    double minX = polygon[ 0 ].X;
    double maxX = polygon[ 0 ].X;
    double minY = polygon[ 0 ].Y;
    double maxY = polygon[ 0 ].Y;
    for ( int i = 1 ; i < polygon.Length ; i++ )
    {
        Point q = polygon[ i ];
        minX = Math.Min( q.X, minX );
        maxX = Math.Max( q.X, maxX );
        minY = Math.Min( q.Y, minY );
        maxY = Math.Max( q.Y, maxY );
    }

    if ( p.X < minX || p.X > maxX || p.Y < minY || p.Y > maxY )
    {
        return false;
    }

    // https://wrf.ecse.rpi.edu/Research/Short_Notes/pnpoly.html
    bool inside = false;
    for ( int i = 0, j = polygon.Length - 1 ; i < polygon.Length ; j = i++ )
    {
        if ( ( polygon[ i ].Y > p.Y ) != ( polygon[ j ].Y > p.Y ) &&
            p.X < ( polygon[ j ].X - polygon[ i ].X ) * ( p.Y - polygon[ i ].Y ) / ( polygon[ j ].Y - polygon[ i ].Y ) + polygon[ i ].X )
        {
            inside = !inside;
        }
    }

    return inside;
}

bool PointLocationCalculator::IsInsideTransformedPolygon(geometry_msgs::Point Polygon[], geometry_msgs::Pose PolygonPose, , geometry_msgs::Pose Point)
{
    double xt = Point.position.x - PolygonPose.position.x;
    double yt = Point.position.y - PolygonPose.position.y;

    tf::Quaternion robot_YAW(PolygonPose.orientation.x, PolygonPose.orientation.y, PolygonPose.orientation.z, PolygonPose.orientation.w);
    double Bot_Yaw = GetPositiveYaw(robot_YAW);
    double radians = (M_PI/180)*degree;

    double xr = (xt*cos(radians)) - (yt*sin(radians));
    double yr = (xt*cos(radians)) + (yt*sin(radians));

    int i, j, c = 0;
    for (i = 0, j = nvert-1; i < nvert; j = i++) {
    if ( ((verty[i]>testy) != (verty[j]>testy)) &&
    (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
        c = !c;
    }
    
    return c;
}
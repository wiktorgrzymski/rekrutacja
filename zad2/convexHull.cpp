#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * @struct Point
 * @brief A struct representing a 2D point with x and y coordinates.
 */
struct Point {
    double x, y;
};

/**
 * @brief Calculate the distance between a point and a line segment.
 *
 * @param a The first point of the line segment.
 * @param b The second point of the line segment.
 * @param p The point for which distance is to be calculated.
 * @return The distance between point p and the line segment defined by points a and b.
 */
double distance(Point a, Point b, Point p) {
    return abs((b.x - a.x) * (a.y - p.y) - (a.x - p.x) * (b.y - a.y)) / sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

/**
 * @brief Find the point with the maximum distance from a line segment.
 *
 * @param points The set of points to search.
 * @param a The first point of the line segment.
 * @param b The second point of the line segment.
 * @return The index of the point in the points vector with the maximum distance from the line segment.
 */
int findMaxDistancePoint(vector<Point>& points, int a, int b) {
    double maxDist = -1;
    int maxPointIndex = -1;

    for (int i = 0; i < points.size(); i++) {
        double dist = distance(points[a], points[b], points[i]);
        if (dist > maxDist) {
            maxDist = dist;
            maxPointIndex = i;
        }
    }

    return maxPointIndex;
}

/**
 * @brief QuickHull algorithm to find the convex hull of a set of points.
 *
 * @param points The set of points.
 * @param left The index of the leftmost point.
 * @param right The index of the rightmost point.
 * @param convexHull The vector to store the points of the convex hull.
 */
void quickHull(vector<Point>& points, int left, int right, vector<Point>& convexHull) {
    if (points.empty() || left >= right) {
        return; // Base case: No points or only one point, nothing to do.
    }

    // Find the referential point as the point with the lowest x-coordinate.
    int referentialIndex = left;
    for (int i = left; i <= right; i++) {
        if (points[i].x < points[referentialIndex].x) {
            referentialIndex = i;
        }
    }

    swap(points[referentialIndex], points[right]);

    int splitIndex = left;
    // Partition points into two sets based on their x-coordinates relative to the referential point.
    for (int i = left; i < right; i++) {
        if (points[i].x < points[right].x) {
            swap(points[i], points[splitIndex]);
            splitIndex++;
        }
    }

    // Swap the referential point to its correct position.
    swap(points[right], points[splitIndex]);

    // Add the referential point to the convex hull. c
    convexHull.push_back(points[splitIndex]);

    // Find the point with the maximum distance from the line segment between left and the referential point.
    int maxDistancePoint = findMaxDistancePoint(points, left, splitIndex);

    // Recursively apply QuickHull to the left and right subproblems.
    quickHull(points, left, splitIndex - 1, convexHull);
    quickHull(points, splitIndex + 1, right, convexHull);
}

/**
 * @brief The main function for the QuickHull convex hull algorithm.
 *
 * This function reads a set of 2D points from the user, calculates the convex hull
 * of the points, and prints the points forming the convex hull.
 */
int main() {
    int n;
    cout << "Enter the number of points: ";
    cin >> n;

    vector<Point> points;

    for (int i = 0; i < n; i++) {
        Point point;
        cout << "Enter coordinates for point " << i + 1 << " (x y): ";
        cin >> point.x >> point.y;
        points.push_back(point);
    }

    vector<Point> convexHull;
    quickHull(points, 0, n - 1, convexHull);

    cout << "Points forming the convex hull:" << endl;
    for (const Point& p : convexHull) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }

    return 0;
}

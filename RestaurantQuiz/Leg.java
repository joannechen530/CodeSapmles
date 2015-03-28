package ca.ubc.cs.cpsc210.quiz.model;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents a leg that has an arbitrary number of points and a distance.  Part of a route.
 */
public class Leg {

    private List<LatLng> points;
    private int distance;


    // Constructor
    public Leg() {
        points = new ArrayList<LatLng>();
        distance = 0;
    }

    // Add a list of points to the leg
    public void addAllPoints(List<LatLng> pts) {
        for (LatLng pt : pts) {
            points.add(pt);
        }
    }

    // Add a point to the leg
    public void addPoint(LatLng pt) {
        points.add(pt);
    }

    // Gets leg distance
    public int getDistance(){
        return distance;
    }

    // Gets all points on this leg
    public List<LatLng> getPoints() {
        return points;
    }

    //Set the distance for this leg
    public void setDistance(int distance) {
        this.distance = distance;
    }


}

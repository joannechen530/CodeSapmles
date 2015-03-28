package ca.ubc.cs.cpsc210.quiz.model;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents a route having a list of legs and a distance.
 */
public class Route {

    private List<Leg> legs;
    private int distance;    //IS DISTANCE SUPPOSED TO BE A FIELD?????

    // Constructor
    public Route() {
        legs = new ArrayList<Leg>();
        distance = 0;
    }

    // Add a leg to this route
    public void addLeg(Leg leg){
        legs.add(leg);
    }

    // Get total distance for this route (the sum of the distances for the legs)
    public int getDistance(){

        for (Leg leg : legs) {
            distance += leg.getDistance();
        }

        return distance;
    }   

    // Get points on this route
    public List<Leg> getLegs(){
        return legs;
    }

}

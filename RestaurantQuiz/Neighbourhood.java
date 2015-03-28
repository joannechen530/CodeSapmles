package ca.ubc.cs.cpsc210.quiz.model;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

/**
 * Represents a neighbourhood having a name in a city
 */
public class Neighbourhood implements GeoArea {

    private String neighborhoodName;
    private City city;

    public Neighbourhood(String neighborhoodName, City city) {
        this.neighborhoodName = neighborhoodName;
        this.city = city;
    }

    /**
     * Two neighbourhoods are equal if they have the same city and same name
     * When o is a City, this neighbourhood is equal to it, if it has the same city.
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;

        // will have to revisit this if we add subtypes of GeoArea other than City and Neighborhood
        if (o == null || !(o instanceof GeoArea)) return false;

        // when o is a City, this Neighborhood is equal to o if the cities are equal
        if (o instanceof City)
            return city.equals(o);

        // must be a Neighborhood
        Neighbourhood other = (Neighbourhood) o;

        return (city.equals(other.city) && neighborhoodName.equals(other.neighborhoodName));
    }

    public List<String> getAllGeoStrings(){

        List<String> geoStrings = new ArrayList<String>();
        String suffix = ", " + getCityString();

        for (int i = 0; i < neighborhoodName.length(); i++) {
            if (neighborhoodName.charAt(i) == " ".charAt(0))
                geoStrings.add(neighborhoodName.substring(0, i) + suffix);
        }
        geoStrings.add(neighborhoodName + suffix);
        return geoStrings;
    }

    public City getCity(){
        return city;
    }

    public String getCityString(){
        return getCity().getCityString();
    }

    @Override
    public int hashCode() {
        return city != null ? city.hashCode() : 0;
    }
}

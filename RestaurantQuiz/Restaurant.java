package ca.ubc.cs.cpsc210.quiz.model;

import java.util.List;

/**
 * Represents a restaurant having a street address, geographical area, postal code, name, id categories
 * and list of reviews.
 */
public class Restaurant {

    private GeoArea geographicalArea;
    private List<Category> categories;

    private String name;
    private String id;
    private String address;
    private String postalCode;

    //Constructor
    public Restaurant(String name, List<Category> categories, String id, String address, String postalCode, GeoArea geographicalArea){
        this.name = name;
        this.categories = categories;
        this.id = id;
        this.address = address;
        this.postalCode = postalCode;
        this.geographicalArea = geographicalArea;
    }

    public String getAddress(){
        return address;
    }

    public List<Category> getCategories(){
        return categories;
    }

    public GeoArea getGeographicalArea(){
        return geographicalArea;
    }

    public String getId(){
        return id;
    }

    public String getName() {
        return name;
    }

    public String getPostalCode(){
        return postalCode;
    }

    @Override
    public String toString() {
        return name + ", " + geographicalArea.getAllGeoStrings().get(0) + ", " + postalCode;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Restaurant that = (Restaurant) o;

        if (address != null ? !address.equals(that.address) : that.address != null) return false;
        if (categories != null ? !categories.equals(that.categories) : that.categories != null) return false;
        if (geographicalArea != null ? !geographicalArea.equals(that.geographicalArea) : that.geographicalArea != null)
            return false;
        if (id != null ? !id.equals(that.id) : that.id != null) return false;
        if (name != null ? !name.equals(that.name) : that.name != null) return false;
        if (postalCode != null ? !postalCode.equals(that.postalCode) : that.postalCode != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = geographicalArea != null ? geographicalArea.hashCode() : 0;
        result = 31 * result + (categories != null ? categories.hashCode() : 0);
        result = 31 * result + (name != null ? name.hashCode() : 0);
        result = 31 * result + (id != null ? id.hashCode() : 0);
        result = 31 * result + (address != null ? address.hashCode() : 0);
        result = 31 * result + (postalCode != null ? postalCode.hashCode() : 0);
        return result;
    }
}
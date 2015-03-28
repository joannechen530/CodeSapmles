package ca.ubc.cs.cpsc210.quiz.model;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents a name having a name, province/state code and country code
 */
public class City implements GeoArea {

    private String cityName;
    private String province;
    private String countryCode;

    // Constructor
    public City(String cityName, String province, String countryCode) throws IllegalArgumentException {
        if (province.length()!=2 || countryCode.length()!=2)
            throw new IllegalArgumentException();
        this.cityName = cityName;
        this.province = province;
        this.countryCode = countryCode;
    }

    public List<String> getAllGeoStrings(){
        List<String> geoStrings = new ArrayList<String>(); //ARRAY OR LINKED??
        geoStrings.add(getCityString());
        return geoStrings;
    }

    public String getCityString(){
        return cityName + ", " + province + ", " + countryCode;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || !(o instanceof GeoArea)) return false;

        if (o instanceof Neighbourhood) {
            Neighbourhood n = (Neighbourhood) o;
            return equals(n.getCity());
        }

        City city = (City) o;

        if (cityName != null ? !cityName.equals(city.cityName) : city.cityName != null) return false;
        if (countryCode != null ? !countryCode.equals(city.countryCode) : city.countryCode != null) return false;
        if (province != null ? !province.equals(city.province) : city.province != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = cityName != null ? cityName.hashCode() : 0;
        result = 31 * result + (province != null ? province.hashCode() : 0);
        result = 31 * result + (countryCode != null ? countryCode.hashCode() : 0);
        return result;
    }
}

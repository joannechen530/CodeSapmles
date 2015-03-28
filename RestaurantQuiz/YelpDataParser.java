package ca.ubc.cs.cpsc210.quiz.yelp;

import ca.ubc.cs.cpsc210.quiz.model.*;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;

/**
 * Parser for JSON data returned by Yelp.
 */
public class YelpDataParser {

    public YelpDataParser(){}
    
    public static List<Restaurant> parseRestaurantData(String response, String yelpCityFilter) throws JSONException {
        JSONObject obj = new JSONObject(response);
        List<Restaurant> restaurants = new ArrayList<Restaurant>();
        JSONArray businesses = obj.getJSONArray("businesses");

        for (int i = 0; i < businesses.length(); i++) {
            JSONObject r = businesses.getJSONObject(i);
            JSONObject l = r.getJSONObject("location");

            if (!r.getBoolean("is_closed") && l.getString("city").equals(yelpCityFilter)) {
                String name = r.getString("name");

                List<Category> categories = new ArrayList<Category>();
                for (int n = 0; n < r.getJSONArray("categories").length(); n++){
                    categories.add(new Category(r.getJSONArray("categories").getJSONArray(n).getString(0),
                            r.getJSONArray("categories").getJSONArray(n).getString(1)));
                }

                String id = r.getString("id");
                String address = l.getJSONArray("address").getString(0);


                String postalCode;
                try {
                    l.getString("postal_code");
                    postalCode = l.getString("postal_code");
                } catch (JSONException e) {
                    postalCode = null;
                }

                City city = new City(l.getString("city"),
                        l.getString("state_code"),
                        l.getString("country_code"));
                GeoArea geoArea = city;
                try {
                    l.getJSONArray("neighborhoods");
                    if (!l.getJSONArray("neighborhoods").isNull(0)) {
                        geoArea = new Neighbourhood(l.getJSONArray("neighborhoods").getString(0), city);
                    }
                } catch (JSONException e) { }


                restaurants.add(new Restaurant(name, categories, id, address, postalCode, geoArea));
            }
        }

        return restaurants;
    }
}

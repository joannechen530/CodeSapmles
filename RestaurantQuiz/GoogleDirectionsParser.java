package ca.ubc.cs.cpsc210.quiz.google;

import ca.ubc.cs.cpsc210.quiz.model.LatLng;
import ca.ubc.cs.cpsc210.quiz.model.Leg;
import ca.ubc.cs.cpsc210.quiz.model.Route;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.List;

/**
 * Parser for response from Google Directions API.
 */
public class GoogleDirectionsParser {


    public GoogleDirectionsParser(){

    }

    public static Route parseRoute(String response) throws JSONException{
        JSONObject obj = new JSONObject(response);
        Route route = new Route();

        JSONArray jlegs = obj.getJSONArray("routes").getJSONObject(0).getJSONArray("legs");

        for (int i = 0; i < jlegs.length(); i++) {

            Leg leg = new Leg();
            int legDistance = jlegs.getJSONObject(i).getJSONObject("distance").getInt("value");

            leg.setDistance(legDistance);

            // points are stored in steps
            for (int n = 0;
                    n < jlegs.getJSONObject(i).getJSONArray("steps").length();
                    n++) {
                List<LatLng> pts = PolylineDecoder.decodePoly(jlegs.getJSONObject(i)
                        .getJSONArray("steps").getJSONObject(n).getJSONObject("polyline").getString("points"));

                for (LatLng pt : pts) {
                    leg.addPoint(pt);
                }
            }
            route.addLeg(leg);
        }
        return route;
    }

}

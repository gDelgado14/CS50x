/**
 * service.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Implements a shuttle service.
 */

// default height
var HEIGHT = 0.8;

// default latitude
var LATITUDE = 42.3745615030193;

// default longitude
var LONGITUDE = -71.11803936751632;

// default heading
var HEADING = 1.757197490907891;

// default number of seats
var SEATS = 10;

// default velocity
var VELOCITY = 50;

// global reference to shuttle's marker on 2D map
var bus = null;

// global reference to 3D Earth
var earth = null;

// global reference to 2D map
var map = null;

// global reference to shuttle
var shuttle = null;

// Total points
var totPts = 0;

// minutes * milliseconds * seconds in a minute
var remTime = 10 * 1000 * 60;

var timeCounter = 0;

var intervalID = setInterval(timer,1000);

// load version 1 of the Google Earth API
google.load("earth", "1");

// load version 3 of the Google Maps API
google.load("maps", "3", {other_params: "sensor=false"});

function timer()
{
    remTime -= 1000;
    
    if (timeCounter % 5 == 0 && remTime > 0)
    {
        $("#announcements").html("Time left: " + Math.round(remTime/60000) + " minutes");
    }
    
    timeCounter++;
}

// once the window has loaded
$(window).load(function() {

    // listen for keydown anywhere in body
    $(document.body).keydown(function(event) {
        return keystroke(event, true);
    });

    // listen for keyup anywhere in body
    $(document.body).keyup(function(event) {
        return keystroke(event, false);
    });

    // listen for click on Drop Off button
    $("#dropoff").click(function(event) {
        dropoff();
    });

    // listen for click on Pick Up button
    $("#pickup").click(function(event) {
        pickup();
    });

    // load application
    load();
});

// unload application
$(window).unload(function() {
    unload();
});

/**
 * Renders seating chart.
 */
function chart()
{
    var house;
    var html = "<ol start='0'>";
    
    for (var i = 0; i < shuttle.seats.length; i++)
    {
        if (shuttle.seats[i] == null)
        {
            html += "<li>Empty Seat</li>";
        }
        else
        {
            for (var p = 0; p < PASSENGERS.length; p++)
            {
                if (PASSENGERS[p].username == shuttle.seats[i])
                {
                    house = PASSENGERS[p].house;
                    break;
                }
            }
            
            switch (house) {
            
            case "Adams House":
                html += "<li class='adams'>" + shuttle.seats[i] + " to Adams house</li>";
                break;
                
            case "Cabot House":
                html += "<li class='cabot'>" + shuttle.seats[i] + " to Cabot house</li>";
                break;
                
            case "Currier House":
                html += "<li class='currier'>" + shuttle.seats[i] + " to Currier house</li>";
                break;
                
            case "Dunster House":
                html += "<li class='dunster'>" + shuttle.seats[i] + " to Dunster house</li>";
                break;
              
            case "Eliot House":
                html += "<li class='eliot'>" + shuttle.seats[i] + " to Eliot house</li>";
                break;
                
            case "Kirkland House":
                html += "<li class='kirkland'>" + shuttle.seats[i] + " to Kirkland house</li>";
                break;
                
            case "Leverett House":
                html += "<li class='leverett'>" + shuttle.seats[i] + " to Leverett house</li>";
                break;
                
            case "Lowell House":
                html += "<li class='lowell'>" + shuttle.seats[i] + " to Lowell house</li>";
                break;
                
            case "Mather House":
                html += "<li class='mather'>" + shuttle.seats[i] + " to Mather house</li>";
                break;
                
            case "Pforzheimer House":
                html += "<li class='pforzheimer'>" + shuttle.seats[i] + " to Pforzheimer house</li>";
                break;
                
            case "Quincy House":
                html += "<li class='quincy'>" + shuttle.seats[i] + " to Quincy house</li>";
                break;
                
            case "Winthrop House":
                html += "<li class='winthrop'>" + shuttle.seats[i] + " to Winthrop house</li>";
         
            }
            
            //html += "<li>" + shuttle.seats[i] + "</li>";
        }
    }
    html += "</ol>";
    $("#chart").html(html);
}

/**
 * Drops up passengers if their stop is nearby.
 */
function dropoff()
{
    //TODO
    
    var counter = 0;
    var d;
    var near = false;
    
    // check if near a house
    for (var house in HOUSES)
    {
         d = shuttle.distance(HOUSES[house].lat, HOUSES[house].lng);
         
         if (d <= 30)
         {
            near = true;
         }
        
    }
    
    if (!near) 
    {
        $("#announcements").html("Not near a house!");
        return;
    }
        
    
    // for each passenger in the shuttle
    for (var i = 0; i <  shuttle.seats.length; i++)
    {
        
        if (shuttle.seats[i] != null)
        {
            for (var j = 0; j < PASSENGERS.length; j++)
            {
                if (PASSENGERS[j].username == shuttle.seats[i])
                {
                    var house = PASSENGERS[j].house;
                    break;
                }
            }
            
            d = shuttle.distance(HOUSES[house].lat, HOUSES[house].lng);
            
            // if nearby current student's house
            if (d <= 30)
            {
                shuttle.seats[i] = null;
                counter++;
                chart();
            }
            
            //chart();
        }
    }
    
    if (counter == 0)
    {
        $("#announcements").html("No passengers live here!");
    }
    else
    {
        $("#announcements").html("Good-Bye!");
        points(counter);
    }
    
}

/**
 * Called if Google Earth fails to load.
 */
function failureCB(errorCode) 
{
    // report error unless plugin simply isn't installed
    if (errorCode != ERR_CREATE_PLUGIN)
    {
        alert(errorCode);
    }
}

/**
 * Handler for Earth's frameend event.
 */
function frameend() 
{
    shuttle.update();
}

/**
 * Called once Google Earth has loaded.
 */
function initCB(instance) 
{
    // retain reference to GEPlugin instance
    earth = instance;

    // specify the speed at which the camera moves
    earth.getOptions().setFlyToSpeed(100);

    // show buildings
    earth.getLayerRoot().enableLayerById(earth.LAYER_BUILDINGS, true);

    // disable terrain (so that Earth is flat)
    earth.getLayerRoot().enableLayerById(earth.LAYER_TERRAIN, false);

    // prevent mouse navigation in the plugin
    earth.getOptions().setMouseNavigationEnabled(false);

    // instantiate shuttle
    shuttle = new Shuttle({
        heading: HEADING,
        height: HEIGHT,
        latitude: LATITUDE,
        longitude: LONGITUDE,
        planet: earth,
        seats: SEATS,
        velocity: VELOCITY
    });

    // synchronize camera with Earth
    google.earth.addEventListener(earth, "frameend", frameend);

    // synchronize map with Earth
    google.earth.addEventListener(earth.getView(), "viewchange", viewchange);

    // update shuttle's camera
    shuttle.updateCamera();

    // show Earth
    earth.getWindow().setVisibility(true);

    // render seating chart
    chart();

    // populate Earth with passengers and houses
    populate();
}

/**
 * Handles keystrokes.
 */
function keystroke(event, state)
{
    
    if (remTime > 0) {
    
        $("#announcements").html("Vrooom!");
        
        // ensure we have event
        if (!event)
        {
            event = window.event;
        }

        // left arrow
        if (event.keyCode == 37)
        {
            shuttle.states.turningLeftward = state;
            return false;
        }

        // up arrow
        else if (event.keyCode == 38)
        {
            shuttle.states.tiltingUpward = state;
            return false;
        }

        // right arrow
        else if (event.keyCode == 39)
        {
            shuttle.states.turningRightward = state;
            return false;
        }

        // down arrow
        else if (event.keyCode == 40)
        {
            shuttle.states.tiltingDownward = state;
            return false;
        }

        // A, a
        else if (event.keyCode == 65 || event.keyCode == 97)
        {
            shuttle.states.slidingLeftward = state;
            return false;
        }

        // D, d
        else if (event.keyCode == 68 || event.keyCode == 100)
        {
            shuttle.states.slidingRightward = state;
            return false;
        }
      
        // S, s
        else if (event.keyCode == 83 || event.keyCode == 115)
        {
            shuttle.states.movingBackward = state;     
            return false;
        }

        // W, w
        else if (event.keyCode == 87 || event.keyCode == 119)
        {
            shuttle.states.movingForward = state;    
            return false;
        }
      
        return true;
        
     }
     else {
     
        $("#announcements").html("Time's up!");
     
     }
     
}

/**
 * Loads application.
 */
function load()
{
    // embed 2D map in DOM
    var latlng = new google.maps.LatLng(LATITUDE, LONGITUDE);
    map = new google.maps.Map($("#map").get(0), {
        center: latlng,
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        scrollwheel: false,
        zoom: 17,
        zoomControl: true
    });

    // prepare shuttle's icon for map
    bus = new google.maps.Marker({
        icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/bus.png",
        map: map,
        title: "you are here"
    });

    // embed 3D Earth in DOM
    google.earth.createInstance("earth", initCB, failureCB);
}


function points(tally)
{
   totPts += tally;

   if (totPts == 98)
   {
       $("#announcements").html("All passengers picked up and dropped off!");
   }
   else
   {
      var html = "<div> Points: " + totPts + "</div>";
      $("#announcements").html(html);
   }
}


/**
 * Picks up nearby passengers.
 */
function pickup()
{
    //TODO  
    var empty = false;
    
    // check to see if seats are empty if not make announcement and return
    for (var i = 0; i <  shuttle.seats.length; i++)
    {
        if (shuttle.seats[i] == null)
        {
            empty = true;
            break;
        }
    }
    
    // no empty seats
    if (!empty)
    {
        $("#announcements").html("All seats full!");
        return;
    }
    
    var counter = 0;
    
    // loop through all passengers
    for (var i = 0; i < PASSENGERS.length; i++)
    {         
        var d = shuttle.distance(PASSENGERS[i].lat, PASSENGERS[i].lng); 
        
        // if within 15 metres
        if (d <= 15)
        {
            
            // if passenger hasn't already been picked up (if marker still there) and isn't a freshman
            if (PASSENGERS[i].m.__gm != null && HOUSES[PASSENGERS[i].house] != null)
            {
            
                // remove GE placemark
                var features = earth.getFeatures();
                features.removeChild(PASSENGERS[i].p);
                counter++;
                
                // remove Google maps marker
                PASSENGERS[i].m.setMap(null);
                
                
                for (var j = 0; j <  shuttle.seats.length; j++)
                {
                    if (shuttle.seats[j] == null)
                    {
                        shuttle.seats[j] = PASSENGERS[i].username;
                        break;
                    }
                        
                }
                
                // render passenger into html chart
                chart();
                break;
            }
        } 
    }
    
    if (counter == 0) {
        $("#announcements").html("Cannot pickup!");
    }
    else {
        $("#announcements").html("Someone is nearby!");
    } 
    
}

/**
 * Populates Earth with passengers and houses.
 */
function populate()
{
    // mark houses
    for (var house in HOUSES)
    {
        // plant house on map
        new google.maps.Marker({
            icon: "https://google-maps-icons.googlecode.com/files/home.png",
            map: map,
            position: new google.maps.LatLng(HOUSES[house].lat, HOUSES[house].lng),
            title: house
        });
    }

    // get current URL, sans any filename
    var url = window.location.href.substring(0, (window.location.href.lastIndexOf("/")) + 1);

    // scatter passengers
    for (var i = 0; i < PASSENGERS.length; i++)
    {
        // pick a random building
        var building = BUILDINGS[Math.floor(Math.random() * BUILDINGS.length)];

        // prepare placemark
        var placemark = earth.createPlacemark("");
        placemark.setName(PASSENGERS[i].name + " to " + PASSENGERS[i].house);

        // prepare icon
        var icon = earth.createIcon("");
        icon.setHref(url + "/img/" + PASSENGERS[i].username + ".jpg");

        // prepare style
        var style = earth.createStyle("");
        style.getIconStyle().setIcon(icon);
        style.getIconStyle().setScale(4.0);

        // prepare stylemap
        var styleMap = earth.createStyleMap("");
        styleMap.setNormalStyle(style);
        styleMap.setHighlightStyle(style);

        // associate stylemap with placemark
        placemark.setStyleSelector(styleMap);

        // prepare point
        var point = earth.createPoint("");
        point.setAltitudeMode(earth.ALTITUDE_RELATIVE_TO_GROUND);
        point.setLatitude(building.lat);
        point.setLongitude(building.lng);
        point.setAltitude(0.0);

        // associate placemark with point
        placemark.setGeometry(point);

        // add placemark to Earth
        earth.getFeatures().appendChild(placemark);

        // add marker to map
        var marker = new google.maps.Marker({
            icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/man.png",
            map: map,
            position: new google.maps.LatLng(building.lat, building.lng),
            title: PASSENGERS[i].name + " at " + building.name
        });

        //TODO: remember passenger's placemark and marker for pick-up's sake
        PASSENGERS[i].lat = building.lat;
        PASSENGERS[i].lng = building.lng;
        PASSENGERS[i].p = placemark;
        PASSENGERS[i].m = marker;
    }
}

/**
 * Handler for Earth's viewchange event.
 */
function viewchange() 
{
    // keep map centered on shuttle's marker
    var latlng = new google.maps.LatLng(shuttle.position.latitude, shuttle.position.longitude);
    map.setCenter(latlng);
    bus.setPosition(latlng);
}

/**
 * Unloads Earth.
 */
function unload()
{
    google.earth.removeEventListener(earth.getView(), "viewchange", viewchange);
    google.earth.removeEventListener(earth, "frameend", frameend);
}

// taken from http://nodejs.org/api/addons.html#addons_object_factory

var addon = require('fruit');

// initialise two objects with weights and calories

var apple = new addon.Fruit(5,7);
var pear  = new addon.Fruit(3,6); 

// display information

console.log("Apple: weight =  " + apple.getWeight() + " calories = " 
                                + apple.getCalories());

console.log("Pear: weight =  " + pear.getWeight() + " calories = "
                                + pear.getCalories());


// taken from http://nodejs.org/api/addons.html#addons_object_factory

var addon = require('fruit');

var apple = new addon.Fruit(5,7);
var pear  = new addon.Fruit(3,6); 

console.log("Apple: weight =  " + apple.getWeight() + " calories = " 
                                + apple.getCalories());

console.log("Pear: weight =  " + pear.getWeight() + " calories = "
                                + pear.getCalories());

console.log("Type of juice: ", apple.getJuice());

var bunch = new addon.Grapes( 50, 2, 2 );

console.log("Calories of a grape: " + bunch.getCalories());   

console.log("Total weight of grapes: " + bunch.getBunchWeight());

console.log("Type of juice: ", bunch.getJuice());

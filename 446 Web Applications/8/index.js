var express = require('express');
var app = express();
var courses = require("./courses.json");
var assignments = require("./assignments.json");

app.set('port', (process.env.PORT || 5000));

app.use(express.static(__dirname + '/public'));

// views is directory for all template files
app.set('views', __dirname + '/views');
app.set('view engine', 'pug');

app.get('/', function(request, response) {
  response.render('pages/index', courses)
});

app.get('/courses/:id', function(req, res) {
  var name = req.params.id
  if (isNaN(+name)) name = name.split('-')[1];
  res.render('pages/course', {course: courses.courses[req.params.id], assignments: assignments[req.params.id]})
});


app.get('/add/:id', function(req, res) {
  var name = req.params.id
  if (isNaN(+name)) name = name.split('-')[1];
  res.render('pages/add', {course: courses.courses[req.params.id], assignments: assignments[req.params.id]})
});

app.listen(app.get('port'), function() {
  console.log('Node app is running on port', app.get('port'));
});


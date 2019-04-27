var express = require('express');
var router = express.Router();

/* GET readings listing. */
router.get('/', function(req, res, next) {
  res.send('respond with a resource');
});

/* POST readings. */
router.post('/', function(req, res, next) {
  // write to a file
  // update display
  res.send(req);
});

module.exports = router;

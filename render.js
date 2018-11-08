// run, `phantomjs render.js`
// requires phantomjs, http://phantomjs.org/screen-capture.html
// captures html page into png or pdf file

var page = require('webpage').create();
//viewportSize being the actual size of the headless browser
page.viewportSize = { width: 1024, height: 768 };
//the clipRect is the portion of the page you are taking a screenshot of
page.clipRect = { top: 0, left: 0, width: 1024, height: 768 };
//the rest of the code is the same as the previous example
page.open('https://www.example.com/index.html', function() {
  page.render('out.pdf');
  phantom.exit();
});

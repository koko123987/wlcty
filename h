const { chromium } = require("playwright");
const ProgressBar = require("progress");
const prettier = require("prettier");
const fs = require("fs");
const prompts = require("prompts");

(async () => {
  const browser = await chromium.launch({
    // Uncomment this line to open the browser 👇
    // headless: false
  });
  let data;
  try {
    const outputFilename = "app.apollo.io.json";
    const page = await browser.newPage();
    await page.setDefaultNavigationTimeout(0);
    await page.goto(
      "https://app.apollo.io/#/people?finderViewId=5b6dfc5a73f47568b2e5f11c&page=1&prospectedByCurrentTeam[]=yes"
    );

    try {
      await page.waitForSelector(
        "div.zp_LDJHm a.crx_mouse_visited.minirpa-s9991"
      );
    } catch {
      console.log(
        "Couldn't find div.zp_LDJHm a.crx_mouse_visited.minirpa-s9991"
      );
    }

    const variable1Eval = () => {
      const element = document.querySelector(
        "div.zp_LDJHm a.crx_mouse_visited.minirpa-s9991"
      );
      return element.textContent.replace(/(\r\n|\n|\r)/gm, "").trim();
    };
    let variable1 = await page.evaluate(variable1Eval);
    if (variable1 === null || variable1 === "") {
      // The content could be dynamically loaded. Waiting a bit...
      await page.waitForTimeout(4000);
      variable1 = await page.evaluate(variable1Eval);
    }
    let formattedVariable1 = variable1;

    console.log({ variable1: formattedVariable1 });
    data = { variable1: formattedVariable1 };
    fs.writeFile(
      outputFilename || `./${new Date()}.json`,
      prettier.format(JSON.stringify(data), {
        parser: "json",
      }),
      (err) => {
        if (err) return console.log(err);
      }
    );
    await browser.close();
  } catch (e) {
    await browser.close();
    throw e;
  }
})();

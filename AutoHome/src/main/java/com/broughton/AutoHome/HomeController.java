package com.broughton.AutoHome;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
public class HomeController {

    @GetMapping("/")
    public String homePage() {

        return "index";
    }

    @GetMapping("/donotdisturb")
    public String doNotDisturb() {
        MqttPublish message = new MqttPublish();
        message.donotdisturb();
        return "redirect:/";
    }


}

import DashboardLayout from "@/pages/Layout/DashboardLayout.vue";

import Dashboard from "@/pages/Dashboard.vue";
import Brightness from "@/pages/Brightness";
import Temperatures from "@/pages/Temperatures";

const routes = [
  {
    path: "/",
    component: DashboardLayout,
    redirect: "/temperatures",
    children: [
      /* {
        path: "dashboard",
        name: "Dashboard",
        component: Dashboard
      }, */
      {
        path: "brightness",
        name: "Luminosités",
        component: Brightness
      },
      {
        path: "temperatures",
        name: "Températures",
        component: Temperatures
      }
    ]
  }
];

export default routes;

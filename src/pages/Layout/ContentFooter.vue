<template>
  <footer class="footer">
    <div class="container">
        <nav>
            <ul>
              <li>
                <router-link :to="{path:'/dashboard'}">Home</router-link>
              </li>
                <li>Victor MONSCH | Romain LEMBO</li>
                <li>
                    <a href="http://www.i3s.unice.fr/~menez/M1Miage/TP2/tp2.pdf" target="blank">
                        Consignes
                    </a>
                </li>
            </ul>
        </nav>
        <div class="copyright text-center">
          &copy; {{ new Date().getFullYear() }} <a href="https://www.creative-tim.com/?ref=mdf-vuejs" target="_blank">Creative Tim</a>, made with <i class="fa fa-heart heart"></i> for a better web
        </div>
    </div>
  </footer>

</template>
<script>
export default {};
</script>
<style>
</style>

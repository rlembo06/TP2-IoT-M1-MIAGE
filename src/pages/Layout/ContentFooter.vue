<template>
  <footer class="footer">
    <div class="container">
        <nav>
            <ul>
              <li>
                <router-link :to="{path:'/temperatures'}">Temperatures</router-link>
              </li>
              <li>
                <router-link :to="{path:'/brightness'}">Luminosités</router-link>
              </li>
                <li>Victor MONSCH | Romain LEMBO</li>
                <li>
                    <a href="http://www.i3s.unice.fr/~menez/M1Miage/TP2/tp2.pdf" target="blank">
                        Consignes
                    </a>
                </li>
            </ul>
        </nav>
    </div>
  </footer>

</template>
<script>
export default {};
</script>
<style>
</style>

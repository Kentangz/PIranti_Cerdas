document.addEventListener("DOMContentLoaded", function () {
    const dataTable = document.getElementById("data-table");
    const pagination = document.getElementById("pagination");
  
    let currentPage = 1;
    const limit = 10;
  
    // Function to fetch data
    function fetchData(page) {
      fetch(`fetch_data.php?page=${page}&limit=${limit}`)
        .then(response => response.json())
        .then(data => {
          // Populate the table
          dataTable.innerHTML = data.data;
  
          // Generate pagination
          generatePagination(data.total, page);
        })
        .catch(error => console.error("Error fetching data:", error));
    }
  
    // Function to generate pagination
    function generatePagination(totalRecords, currentPage) {
      const totalPages = Math.ceil(totalRecords / limit);
      let paginationHTML = "";
  
      // Previous button
      paginationHTML += `
        <li class="page-item ${currentPage === 1 ? "disabled" : ""}">
          <button class="page-link" data-page="${currentPage - 1}">Previous</button>
        </li>`;
  
      // Page numbers
      for (let i = 1; i <= totalPages; i++) {
        paginationHTML += `
          <li class="page-item ${i === currentPage ? "active" : ""}">
            <button class="page-link" data-page="${i}">${i}</button>
          </li>`;
      }
  
      // Next button
      paginationHTML += `
        <li class="page-item ${currentPage === totalPages ? "disabled" : ""}">
          <button class="page-link" data-page="${currentPage + 1}">Next</button>
        </li>`;
  
      pagination.innerHTML = paginationHTML;
  
      // Add event listeners to pagination buttons
      const pageLinks = pagination.querySelectorAll(".page-link");
      pageLinks.forEach(link => {
        link.addEventListener("click", function () {
          const page = parseInt(this.dataset.page, 10);
          if (page > 0 && page <= totalPages) {
            currentPage = page;
            fetchData(page);
          }
        });
      });
    }
  
    // Initial data fetch
    fetchData(currentPage);
  });
  
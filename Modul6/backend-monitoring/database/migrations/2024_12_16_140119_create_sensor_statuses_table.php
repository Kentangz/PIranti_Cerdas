<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

return new class extends Migration
{
    /**
     * Run the migrations.
     */
    public function up()
    {
        Schema::create('sensor_status', function (Blueprint $table) {
            $table->id();
            $table->string('status'); // Status sensor, contoh: "Datar" atau "Miring"
            $table->timestamps();    // Kolom untuk created_at dan updated_at
        });
    }
    

    /**
     * Reverse the migrations.
     */
    public function down(): void
    {
        Schema::dropIfExists('sensor_statuses');
    }
};

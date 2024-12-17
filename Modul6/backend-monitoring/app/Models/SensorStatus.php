<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class SensorStatus extends Model
{
    use HasFactory;

    protected $table = 'sensor_status'; // Nama tabel di database
    protected $fillable = ['status'];   // Kolom yang bisa diisi
}


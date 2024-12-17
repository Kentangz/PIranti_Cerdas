<?php

namespace App\Http\Controllers;

use App\Models\SensorStatus;
use Illuminate\Http\Request;

class SensorController extends Controller
{
    // Mendapatkan data status sensor
    public function index()
    {
        return SensorStatus::orderBy('created_at', 'desc')->take(10)->get();
    }

    // Menyimpan data status sensor
    public function store(Request $request)
    {
        $request->validate([
            'status' => 'required|string',
        ]);

        $sensor = SensorStatus::create([
            'status' => $request->status,
        ]);

        return response()->json($sensor, 201);
    }
}

